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


WorkspaceController::WorkspaceController(Sun::Workspace* workspace)
    : _Workspace(workspace),
      _MouseEventData(nullptr),
      _CurrentTool(nullptr),
      _CurrentEditor(nullptr),
      _ActiveViewport(nullptr),
      _HudManager(nullptr) 
{
    assert(_Workspace != nullptr);
    connect(_Workspace, &Sun::Workspace::GridChanged, this, &WorkspaceController::_Workspace_GridChanged);
    connect(Viewport::SignalHub(), &ViewPortSignalHub::ViewportChanged, this, &WorkspaceController::_Viewport_ViewportChanged);

    _VisualObjectManager = new VisualObjectManager(this);

    _RedrawTimer = new QTimer(this);
    _RedrawTimer->setInterval(1000 / 60); 
    connect(_RedrawTimer, &QTimer::timeout, this, &WorkspaceController::_RedrawTimer_Tick);
    _RedrawTimer->start();

    InitWorkspace();
}

void WorkspaceController::InitWorkspace() {
    // init V3dViewer and AisContext
    Workspace()->initV3dViewer();
    Workspace()->initAisContext();
    initVisualSettings();

    // 遍历所有 Viewport 并添加到 _viewControllers 列表
    for (auto& view : Workspace()->viewports()) {
        _ViewportControllers.append(new ViewportController(view, this));
    }

    // 创建并显示网格
    _Grid = new AISX_Grid();

    AisHelper::disableGlobalClipPlanes(_Grid);

    if (Workspace()->aisContext()) {
       Workspace()->aisContext()->Display(_Grid, 0, -1, false);
    }

    //// 初始化 VisualObjects 并更新网格
    //visualObjects.initEntities();
    _UpdateGrid();
}

Tool* WorkspaceController::currentTool() const { 
    return _CurrentTool; 
}

bool WorkspaceController::startTool(Tool* tool) {
    qDebug() << "Debug: _WorkspaceController::startTool";
    try {
        if (currentTool() != nullptr && !cancelTool(currentTool(), true)) {
            return false;
        }
        if (tool != nullptr) {
            tool->setWorkspaceController(this);
            _CurrentTool = tool;
            if (_CurrentEditor) { 
                _CurrentEditor->stopTool(); 
            }
            if (!tool->start()) {
                return false;
            }

            Invalidate(true);
            return true;
        }
        return false;
    }
    catch (std::exception& e) {
        qDebug() << e.what();
        return false;
    }
}

void WorkspaceController::Invalidate(bool immediateOnly, bool forceRedraw) {
    _Workspace->setNeedsImmediateRedraw(true);
    if (!immediateOnly)
        _Workspace->setNeedsRedraw(true);

    if (forceRedraw)
        _Redraw();
}

void WorkspaceController::_Workspace_GridChanged(Sun::Workspace* sender) 
{
    if (_Workspace == sender) {
        recalculateGridSize();
        _GridNeedsUpdate = true;
        _UpdateGrid();
        Invalidate();
    }
}

void WorkspaceController::_Viewport_ViewportChanged(Viewport* sender) 
{
    if (std::any_of(_ViewportControllers.begin(), _ViewportControllers.end(),
        [sender](ViewportController* vc) {
            return vc->viewport() == sender;
        })) {
        _RecalculateGridSize();
        _UpdateParameter();
        Invalidate();
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

    WorkingContext* wc = Workspace()->workingContext();

    if (Workspace()->gridEnabled())
    {
        gp_Ax3 position = wc->workingPlane().Position();
        if (wc->gridRotation() != 0)
        {
            position.Rotate(wc->workingPlane().Axis(), wc->gridRotation());
        }
        _Grid->SetPosition(position);
        _Grid->SetExtents(_LastGridSize.X(), _LastGridSize.Y());
        _Grid->SetDivisions(wc->gridStep(), wc->gridDivisions() * M_PI / 180.0);

        if (wc->gridType() == Sun::Workspace::GridTypes::Rectangular)
        {
            Workspace()->aisContext()->SetDisplayMode(_Grid, 1, false);
        }
        else
        {
            Workspace()->aisContext()->SetDisplayMode(_Grid, 2, false);
        }
    }
    else
    {
        Workspace()->aisContext()->SetDisplayMode(_Grid, 0, false);
    }

    _GridNeedsUpdate = false;
}

void WorkspaceController::initVisualSettings() 
{
    auto aisContext = Workspace()->aisContext();

    // _UpdateParameter();

    // Higlight Selected
    auto selectionDrawer = new Prs3d_Drawer();
    selectionDrawer->SetupOwnDefaults();
    selectionDrawer->SetColor(Colors::Selection.ToQuantityColor());
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
    hilightDrawer->SetColor(Colors::Highlight.ToQuantityColor());
    hilightDrawer->SetDisplayMode(0);
    hilightDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());
    aisContext->SetHighlightStyle(Prs3d_TypeOfHighlight::Prs3d_TypeOfHighlight_Dynamic, hilightDrawer);

    // Higlight Local
    auto hilightLocalDrawer = new Prs3d_Drawer();
    hilightLocalDrawer->SetupOwnDefaults();
    hilightLocalDrawer->SetColor(Colors::Highlight.ToQuantityColor());
    hilightLocalDrawer->SetDisplayMode(1);
    hilightLocalDrawer->SetZLayer(-2); // Graphic3d_ZLayerId_Top
    hilightLocalDrawer->SetTypeOfDeflection(Aspect_TypeOfDeflection::Aspect_TOD_RELATIVE);
    hilightLocalDrawer->SetDeviationAngle(aisContext->DeviationAngle());
    hilightLocalDrawer->SetDeviationCoefficient(aisContext->DeviationCoefficient());

    auto shadingAspect = new Prs3d_ShadingAspect();
    shadingAspect->SetColor(Colors::Highlight.ToQuantityColor());
    shadingAspect->SetTransparency(0);
    shadingAspect->Aspect()->SetPolygonOffsets(Aspect_PolygonOffsetMode::Aspect_POM_Fill, 0.99f, 0.0f);
    hilightLocalDrawer->SetShadingAspect(shadingAspect);

    auto lineAspect = new Prs3d_LineAspect(Colors::Highlight.ToQuantityColor(), Aspect_TypeOfLine::Aspect_TOL_SOLID, 3.0);
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
    
    
    qDebug() << "Debug: _WorkspaceController::mouseMove: " << pos;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseMove(_MouseEventData))
            break;
    }
}

void WorkspaceController::mouseDown(ViewportController* viewportController, Qt::KeyboardModifiers modifiers) {
    qDebug() << "Debug: _WorkspaceController::mouseDown: " << modifiers;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseDown(_MouseEventData))
            break;
    }
}

void WorkspaceController::mouseUp(ViewportController* viewportController, Qt::KeyboardModifiers modifiers) {
    qDebug() << "Debug: _WorkspaceController::mouseUp: " << modifiers;
    for (const auto& handler : enumerateControls()) {
        if (handler->onMouseUp(_MouseEventData))
            break;
    }
}

void WorkspaceController::recalculateGridSize() {
}

bool WorkspaceController::cancelTool(Tool* tool, bool force) {
    return true;
}

Sun::Workspace* WorkspaceController::Workspace() const { 
    return _Workspace; 
}

void WorkspaceController::SetActiveViewport(Viewport* viewport) {
     _ActiveViewport = viewport;
 }

void WorkspaceController::setHudManager(IHudManager* hudManager) { 
    _HudManager = hudManager; 
}

ViewportController* WorkspaceController::viewportController(Viewport* viewport) {
    if (viewport == nullptr) {
        return nullptr;
    }

    auto it = std::find_if(_ViewportControllers.begin(), _ViewportControllers.end(),
        [viewport](const ViewportController* vc) {
            return vc->viewport() == viewport;
        });

    return (it != _ViewportControllers.end()) ? *it : nullptr;
}

void WorkspaceController::dispose() {}

QList<WorkspaceControl*> WorkspaceController::enumerateControls() {
    qDebug() << "Debug: _WorkspaceController::enumerateControls";
    QList<WorkspaceControl*> controls;

    if (_CurrentTool) {
        controls.push_back(_CurrentTool);
    }

    if (_CurrentEditor) {
        controls.push_back(_CurrentEditor);
    }

    return controls;
}
