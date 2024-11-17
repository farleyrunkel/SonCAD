// Copyright [2024] SunCAD

#ifndef SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_
#define SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_

#include <QObject>
#include <QPointer>

#include <gp_Pln.hxx>
#include <gp_Pnt2d.hxx>

#include "Iact/Framework/Tool.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/HudElements/Coord2DHudElement.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/Visual/VisualObject.h"

class CreateBoxTool : public Tool {
	Q_OBJECT

public:
	enum Phase {
		PivotPoint,
		BaseRect,
		Height
	};

public:
	CreateBoxTool();

protected:
	virtual bool OnStart() override;

private:
	void _PivotAction_Preview(PointAction::EventArgs* args);
	void _PivotAction_Finished(PointAction::EventArgs* args);

private:
	Phase m_currentPhase;
	gp_Pln _Plane;
	double _Height;
	bool _IsTemporaryVisual;
	Coord2DHudElement* _Coord2DHudElement;
	QPointer<VisualObject> _VisualShape;
};

#endif // SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_
