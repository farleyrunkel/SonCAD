// Copyright [2024] SunCAD

#ifndef IACT_FRAMEWORK_TOOL_H_
#define IACT_FRAMEWORK_TOOL_H_

#include <QObject>
#include <QString>
#include <vector>

#include <boost/signals2.hpp>

#include <NCollection_Vector.hxx>

#include "Core/Topology/InteractiveEntity.h"
#include "Iact/Framework/ToolAction.h"
#include "Iact/Framework/WorkspaceControl.h"

DEFINE_STANDARD_HANDLE(Tool, WorkspaceControl);

class Tool : public WorkspaceControl
{
public:
	explicit Tool();

public:
	bool Start();

	virtual bool OnStart();

	Handle(ToolAction) CurrentAction() const;

	bool Cancel(bool force);

	void Stop();

	virtual bool PrepareUndo();

protected:
	virtual NCollection_Vector<Handle(WorkspaceControl)> GetChildren() const override;

	virtual bool OnCancel();

	virtual void OnStop();

	virtual void Cleanup() override;

	//void BaseCleanup() {
	//	CleanedUp = true;
	//}

	bool StartAction(Handle(ToolAction)  toolAction, bool exclusive = true);

	void StopAction(Handle(ToolAction)  toolAction);

	void StopAllActions();

public:
	boost::signals2::signal<void(Handle(ToolAction))> ToolActionChanged;

private:
	NCollection_Vector<Handle(ToolAction)> _ToolActions;
	NCollection_Vector<Handle(InteractiveEntity)> _OverriddenVisualShapes;

	bool _IsActive;
};

#endif  // IACT_FRAMEWORK_TOOL_H_
