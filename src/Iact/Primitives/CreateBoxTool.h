// Copyright [2024] SunCAD

#ifndef SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_
#define SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_

#include <QObject>

#include <gp_Pln.hxx>
#include <gp_Pnt2d.hxx>

#include "Iact/Framework/Tool.h"
#include "Iact/ToolActions/PointAction.h"
#include "Iact/HudElements/Coord2DHudElement.h"

class CreateBoxTool : public Tool {
	Q_OBJECT

 public:
	CreateBoxTool();

	enum Phase {
		PivotPoint,
		BaseRect,
		Height
	};

 protected:
	bool onStart() override;

 private:
	void _PivotAction_Finished() {};
	void _PivotAction_Preview() {};

 private:
	Phase m_currentPhase;
	gp_Pln _Plane;
	double _Height;
	bool _IsTemporaryVisual;
	Coord2DHudElement* m_coord2DHudElement;
};

#endif // SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_
