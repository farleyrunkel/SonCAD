#ifndef _ToolAction_h
#define _ToolAction_h

#include <vector>

#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceController;

class ToolAction : public WorkspaceControl
{
public:
	explicit ToolAction() {}

	// Start and stop functions
	bool start() { return onStart(); }
	virtual void reset() { m_isFinished = false; }
	void stop() { onStop();}

	bool isFinished() const { return m_isFinished; }

protected:
	virtual bool onStart() { return false; }
	virtual void onStop() {}

private:
	bool m_isFinished;
};

#endif // !_ToolAction_h
