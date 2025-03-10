#ifndef _Tool_h
#define _Tool_h

#include <vector>

 
#include "Core/Topology/InteractiveEntity.h"
#include "Iact/Framework/WorkspaceControl.h"

class WorkspaceController;


class Tool : public WorkspaceControl
{
public:
	explicit Tool() {}

private:
	std::vector<std::shared_ptr<Tool>> myActions;
	std::vector<std::shared_ptr<InteractiveEntity>> myOverriddenVisualShapes;
};

#endif // !_Tool_h
