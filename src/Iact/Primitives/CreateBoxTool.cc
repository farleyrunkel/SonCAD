// Copyright [2024] SunCAD

#include "Iact/Primitives/CreateBoxTool.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/HudElements/MultiValueHudElement.h"
#include "Iact/Workspace/WorkspaceController.h"

namespace {
    double RoundToNearest(double value, double divider) {
        return std::round(value / divider) * divider;
    }
}

CreateBoxTool::CreateBoxTool() 
	: Tool()
{	
}

bool CreateBoxTool::OnStart() {
	qDebug() << "Debug: CreateBoxTool::OnStart";
	_CurrentPhase = Phase::PivotPoint;
	auto pointAction = new PointAction();
	if (!StartAction(pointAction)) {
		return false;
	}

	connect(pointAction, &PointAction::Preview, this, &CreateBoxTool::_PivotAction_Preview);
	connect(pointAction, &PointAction::Finished, this, &CreateBoxTool::_PivotAction_Finished);

	SetHintMessage("Select corner point.");
	_Coord2DHudElement = new Coord2DHudElement;
	Add(_Coord2DHudElement);
	return true;
}

void CreateBoxTool::_EnsurePreviewShape() {}

void CreateBoxTool::_PivotAction_Preview(PointAction::EventArgs* args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Preview";
	if (_Coord2DHudElement) {
		_Coord2DHudElement->SetValues(args->Point.X(), args->Point.Y());
	}
}

void CreateBoxTool::_PivotAction_Finished(PointAction::EventArgs* args) {
	qDebug() << "Debug: CreateBoxTool::_PivotAction_Finished";

	PointAction* action = qobject_cast<PointAction*>(sender());
	if (action == nullptr) {
		return;
	}

	_Plane = WorkspaceController()->Workspace()->WorkingPlane();
	_PointPlane1 = args->PointOnPlane;

	StopAction(action);
	auto newAction = new PointAction();

	connect(newAction, &PointAction::Preview, this, &CreateBoxTool::_BaseRectAction_Preview);
	connect(newAction, &PointAction::Finished, this, &CreateBoxTool::_BaseRectAction_Finished);

	if (!StartAction(newAction))
		return;

	_CurrentPhase = Phase::BaseRect;
	SetHintMessage("Select opposite corner point, press `k:Ctrl` to round length and width to grid stepping.");

	if (_MultiValueHudElement == nullptr)
	{
		_MultiValueHudElement = new MultiValueHudElement();
		_MultiValueHudElement->SetLabel("Length:", "Width:");
		connect(_MultiValueHudElement, &MultiValueHudElement::MultiValueEntered, 
				this, &CreateBoxTool::_MultiValueEntered);
		Add(_MultiValueHudElement);
	}
}

void CreateBoxTool::_BaseRectAction_Preview(PointAction::EventArgs* args) 
{
    if (args != nullptr)
    {
        _PointPlane2 = args->PointOnPlane;
    }

    double dimX = std::abs(_PointPlane1.X() - _PointPlane2.X());
    double dimY = std::abs(_PointPlane1.Y() - _PointPlane2.Y());

    if (args && args->MouseEventData->modifierKeys.testFlag(Qt::ControlModifier))
    {
        dimX = ::RoundToNearest(dimX, WorkspaceController()->Workspace()->GridStep());
        dimY = ::RoundToNearest(dimY, WorkspaceController()->Workspace()->GridStep());
    }

    if (std::abs(dimX) <= 0.0)
    {
        dimX = 0.001;
    }
    if (std::abs(dimY) <= 0.0)
    {
        dimY = 0.001;
    }

    double posX = 0.0;
    if (_PointPlane1.X() < _PointPlane2.X())
    {
        posX = _PointPlane1.X();
        _PointPlane2.SetX(_PointPlane1.X() + dimX);
    }
    else
    {
        posX = _PointPlane1.X() - dimX;
        _PointPlane2.SetX(posX);
    }

    double posY = 0.0;
    if (_PointPlane1.Y() < _PointPlane2.Y())
    {
        posY = _PointPlane1.Y();
        _PointPlane2.SetY(_PointPlane1.Y() + dimY);
    }
    else
    {
        posY = _PointPlane1.Y() - dimY;
        _PointPlane2.SetY(posY);
    }

    _EnsurePreviewShape();

    auto position = ElSLib::Value(posX, posY, _Plane);
    position.SetX(std::round(position.X()));
    position.SetY(std::round(position.Y()));
    position.SetZ(std::round(position.Z()));
    //_PreviewShape->BodY()->SetPosition(position);
    //_PreviewShape->SetDimensionX(dimX);
    //_PreviewShape->SetDimensionY(dimY);

    //if (_IsTemporaryVisual)
    //{
    //    if (_VisualShape)
    //    {
    //        _VisualShape->Update();
    //    }
    //}

    //if (args)
    //{
    //    args->MarkerPosition = ElSLib::Value(_PointPlane2.X(), _PointPlane2.Y(), _Plane).rounded();
    //}

    //if (_Coord2DHudElement)
    //{
    //    _Coord2DHudElement->SetValues(_PointPlane2.X(), _PointPlane2.Y());
    //}
    //if (_MultiValueHudElement)
    //{
    //    _MultiValueHudElement->SetValues(dimX, dimY);
    //}

    //WorkspaceController::Instance()->Invalidate();
}


void CreateBoxTool::_BaseRectAction_Finished(PointAction::EventArgs* args) 
{

}

void CreateBoxTool::_MultiValueEntered(double newValue1, double newValue2)
{
	if (_CurrentPhase == Phase::BaseRect)
	{
		_PointPlane2 = gp_Pnt2d(_PointPlane1.X() + newValue1, _PointPlane1.Y() + newValue2);
		_BaseRectAction_Preview(nullptr);
		_EnsurePreviewShape();
		_BaseRectAction_Finished(nullptr);
	}
}
