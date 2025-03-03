#ifndef _CoreContext_h_
#define _CoreContext_h_

#include "Core/Project/Workspace.h"
#include "Core/Project/Viewport.h"

class CoreContext
{
public:
	CoreContext() {};
	virtual ~CoreContext() {};

	static CoreContext* Current()
	{
		return myCurrent;
	}

private:
	Handle(Workspace) myWorkspace;
	Handle(Viewport) myViewport;
	Handle(Document) myDocument;

private:
	static CoreContext* myCurrent;

	CoreContext(const CoreContext&) = delete;
};

#endif // !_CoreContext_h_
