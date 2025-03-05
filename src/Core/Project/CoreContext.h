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
		return m_Current;
	}

private:
	std::shared_ptr<Workspace> m_Workspace;
	std::shared_ptr<Viewport> m_Viewport;
	std::shared_ptr<Document> m_Document;

private:
	static CoreContext* m_Current;
};

#endif // !_CoreContext_h_
