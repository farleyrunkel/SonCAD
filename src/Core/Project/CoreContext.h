#ifndef _CoreContext_h_
#define _CoreContext_h_

#include "Core/Project/Workspace.h"
#include "Core/Project/Viewport.h"

class CoreContext
{
public:
	static CoreContext* Current()
	{
		static CoreContext aContext;
		return &aContext;
	}

private:
	Handle(Workspace) myWorkspace;
	Handle(Viewport) myViewport;
	Handle(Document) myDocument;

private:
	CoreContext() {};
	CoreContext(const CoreContext&) = delete;
};

#endif // !_CoreContext_h_
