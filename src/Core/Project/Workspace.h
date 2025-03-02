#ifndef _Workspace_h_
#define _Workspace_h_

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pln.hxx>
#include <NCollection_List.hxx>
#include <Standard_Transient.hxx>
#include <V3d_Viewer.hxx>

// Forward declaire
class WorkingContext;
class Document;
class Viewport;

DEFINE_STANDARD_HANDLE(Workspace, Standard_Transient)

class Workspace final : public Standard_Transient
{
	using GridChangedSignal = boost::signals2::signal<void(Workspace*)>;

public:
	enum GridTypes
	{
		Rectangular,
		Circular
	};

public:
	explicit Workspace() {}

	GridChangedSignal& GridChanged()
	{
		return myGridChanged;
	}

public:
	GridChangedSignal myGridChanged;

private:
	NCollection_List<Handle(Viewport)> myViewports;

	Handle(Document) myDocument;
	Handle(V3d_Viewer) myViewer;
	Handle(AIS_InteractiveContext) myContext;

	bool myNeedsRedraw;
	bool myNeedsImmediateRedraw;
	bool myGridEnabled;

	GridTypes myGridType;
	double myGridStep;
	double myGridRotation;
	int myGridDivisions;

	gp_Pln myWorkingPlane;

	Handle(WorkingContext) myGlobalWorkingContext;
	Handle(WorkingContext) myWorkingContext;
};

#endif // !_Workspace_h_
