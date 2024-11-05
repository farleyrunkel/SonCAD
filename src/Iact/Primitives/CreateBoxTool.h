// Copyright [2024] SunCAD

#ifndef SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_
#define SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_

#include <QObject>

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
	Coord2DHudElement* m_coord2DHudElement;
	Phase m_currentPhase;
};

#endif // SRC_IACT_PRIMITIVES_CREATEBOXTOOL_H_
