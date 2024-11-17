// Copyright [2024] SunCAD

#include "Iact/Workspace/WorkspaceController.h"

#include <algorithm>

#include <QDebug>

#include "Core/Project/WorkingContext.h"
#include "Iact/Workspace/ViewportController.h"
#include "Iact/Framework/Tool.h"
#include "Iact/Visual/Marker.h"
#include "Occt/ValueTypes/Ax3.h"

#include <gp_Ax3.hxx>


WorkspaceController::WorkspaceController(Workspace* workspace)
    : m_workspace(workspace),
      m_mouseEventData(nullptr),
      m_currentTool(nullptr),
      m_currentEditor(nullptr),
      m_activeViewport(nullptr),
      _HudManager(nullptr) {

    connect(m_workspace, &Workspace::gridChanged, this, &WorkspaceController::onWorkspaceGridChanged);

    initWorkspace();
}

void WorkspaceController::initWorkspace() {
    // init V3dViewer and AisContext
    workspace()->initV3dViewer();
    workspace()->initAisContext();
    initVisualSettings();

    // 遍历所有 Viewport 并添加到 _viewControllers 列表
    for (auto& view : workspace()->viewports()) {
        m_viewportControllers.append(new ViewportController(view, this));
    }

    // 创建并显示网格
    _Grid = new AISX_Grid();

    AisHelper::disableGlobalClipPlanes(_Grid);

    if (workspace()->aisContext()) {
       workspace()->aisContext()->Display(_Grid, 0, -1, false);
    }

    //// 初始化 VisualObjects 并更新网格
    //visualObjects.initEntities();
    _UpdateGrid();
}

Tool* WorkspaceController::currentTool() const { 
    return m_currentTool; 
}

bool WorkspaceController::startTool(Tool* tool) {
    qDebug() << "Debug: m_workspaceController::startTool";
    try {
        if (currentTool() != nullptr && !cancelTool(currentTool(), true)) {
            return false;
        }
        if (tool != nullptr) {
            tool->setWorkspaceController(this);
            m_currentTool = tool;
            if (m_currentEditor) { 
                m_currentEditor->stopTool(); 
            }
            if (!tool->start()) {
                return false;
            }

            invalidate(true);
            return true;
        }
        return false;
    }
    catch (std::exception& e) {
        qDebug() << e.what();
        return false;
    }
}

void WorkspaceController::invalidate(bool immediateOnly, bool forceRedraw) {
    m_workspace->setNeedsImmediateRedraw(true);
    if (!immediateOnly)
        m_workspace->setNeedsRedraw(true);

    if (forceRedraw)
        _Redraw();
}

void WorkspaceController::onWorkspaceGridChanged(Workspace* sender) {
    if (m_workspace == sender) {
        recalculateGridSize();
        _GridNeedsUpdate = true;
        _UpdateGrid();
        invalidate();
    }
}

void WorkspaceController::_Redraw() 
{
}

void WorkspaceController::_UpdateGrid() 
{
    if (!_GridNeedsUpdate)
        return;

    if (_Grid.IsNull())
        return;

    WorkingContext* wc = workspace()->workingContext();

    if (workspace()->gridEnabled())
    {
        gp_Ax3 position = wc->workingPlane().Position();
        if (wc->gridRotation() != 0)
        {
            position.Rotate(wc->workingPlane().Axis(), wc->gridRotation());
        }
        _Grid->SetPosition(position);
        _Grid->SetExtents(_LastGridSize.X(), _LastGridSize.Y());
        _Grid->SetDivisions(wc->gridStep(), wc->gridDivisions() * M_PI / 180.0);

        if (wc->gridType() == Workspace::GridTypes::Rectangular)
        {
            workspace()->aisContext()->SetDisplayMode(_Grid, 1, false);
        }
        else
        {
            workspace()->aisContext()->SetDisplayMode(_Grid, 2, false);
        }
    }
    else
    {
        workspace()->aisContext()->SetDisplayMode(_Grid, 0, false);
    }

    _GridNeedsUpdate = false;
}

void WorkspaceController::initVisualSettings() 
{
    auto aisContext = workspace()->aisContext();

    // _UpdateParameter();

    // Higlight Selected
    auto selectionDrawer = new Prs3d_Drawer();
    selectionDrawer->SetupOwnDefaults();
    selectionDrawer->SetColor(Colors::Selection.toQuantityColor());
    selectionDrawer->SetDisplayMode(0);
    selectionDrawer->SetZLayer(0); // Graphic3d_ZLayerId_Default
    selectionDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    selectionDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    selectionDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());
    aisContext->SetSelectionStyle(selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Selected, selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalSelected, selectionDrawer);
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_SubIntensity, selectionDrawer);

    // Higlight Dynamic
    auto hilightDrawer = new Prs3d_Drawer();
    hilightDrawer->SetupOwnDefaults();
    hilightDrawer->SetColor(Colors::Highlight.toQuantityColor());
    hilightDrawer->SetDisplayMode(0);
    hilightDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Dynamic, hilightDrawer);

    // Higlight Local
    auto hilightLocalDrawer = new Prs3d_Drawer();
    hilightLocalDrawer->SetupOwnDefaults();
    hilightLocalDrawer->SetColor(Colors::Highlight.toQuantityColor());
    hilightLocalDrawer->SetDisplayMode(1);
    hilightLocalDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightLocalDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightLocalDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightLocalDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());

    auto shadingAspect = new Prs3d_ShadingAspect();
    shadingAspect->SetColor(Colors::Highlight.toQuantityColor());
    shadingAspect->SetTransparency(0);
    shadingAspect->Aspect()->SetPolygonOffsets(Aspect_PolygonOffsetMode::Aspect_POM_Fill, 0.99f, 0.0f);
    hilightLocalDrawer->SetShadingAspect(shadingAspect);

    auto lineAspect = new Prs3d_LineAspect(Colors::Highlight.toQuantityColor(), Aspect_TypeOfLine::Aspect_TOL_SOLID, 3.0);
    hilightLocalDrawer->SetLineAspect(lineAspect);
    hilightLocalDrawer->SetSeenLineAspect(lineAspect);
    hilightLocalDrawer->SetWireAspect(lineAspect);
    hilightLocalDrawer->SetFaceBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetFreeBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetUnFreeBoundaryAspect(lineAspect);
    hilightLocalDrawer->SetPointAspect(Marker::CreateBitmapPointAspect(Marker::BallImage(), Colors::Highlight));

    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_LocalDynamic, hilightLocalDrawer);
}

void WorkspaceController::mouseMove(ViewportController* viewportController, QPointF pos, Qt::KeyboardModifiers modifiers) {
    qDebug() << "Debug: m_workspaceController::mouseMove: " << pos;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseMove(m_mouseEventData))
            break;
    }
}

void WorkspaceController::mouseDown(ViewportController* viewportController, Qt::KeyboardModifiers modifiers) {
    qDebug() << "Debug: m_workspaceController::mouseDown: " << modifiers;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseDown(m_mouseEventData))
            break;
    }
}

void WorkspaceController::mouseUp(ViewportController* viewportController, Qt::KeyboardModifiers modifiers) {
    qDebug() << "Debug: m_workspaceController::mouseUp: " << modifiers;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseUp(m_mouseEventData))
            break;
    }
}

void WorkspaceController::recalculateGridSize() {
}

bool WorkspaceController::cancelTool(Tool* tool, bool force) {
    return true;
}

Workspace* WorkspaceController::workspace() const { 
    return m_workspace; 
}

void WorkspaceController::setActiveViewport(Viewport* viewport) {
     m_activeViewport = viewport;
 }

void WorkspaceController::setHudManager(IHudManager* hudManager) { 
    _HudManager = hudManager; 
}

ViewportController* WorkspaceController::viewportController(Viewport* viewport) {
    if (viewport == nullptr) {
        return nullptr;
    }

    auto it = std::find_if(m_viewportControllers.begin(), m_viewportControllers.end(),
        [viewport](const ViewportController* vc) {
            return vc->viewport() == viewport;
        });

    return (it != m_viewportControllers.end()) ? *it : nullptr;
}

void WorkspaceController::dispose() {}

QList<WorkspaceControl*> WorkspaceController::enumerateControls() {
    qDebug() << "Debug: m_workspaceController::enumerateControls";
    QList<WorkspaceControl*> controls;

    if (m_currentTool) {
        controls.push_back(m_currentTool);
    }

    if (m_currentEditor) {
        controls.push_back(m_currentEditor);
    }

    return controls;
}
