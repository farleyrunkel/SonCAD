#ifndef _CoreContext_h_
#define _CoreContext_h_

#include "Core/Project/Workspace.h"
#include "Core/Project/Viewport.h"

class CoreContext
{
public:
	CoreContext() {};
	CoreContext(const CoreContext&) = delete;

	virtual ~CoreContext() {};

	static CoreContext* Current()
	{
		return myCurrent;
	}

private:
	std::shared_ptr<Workspace> myWorkspace;
	std::shared_ptr<Viewport> myViewport;
	std::shared_ptr<Document> myDocument;

private:
	static CoreContext* myCurrent;
};

#endif // !_CoreContext_h_
