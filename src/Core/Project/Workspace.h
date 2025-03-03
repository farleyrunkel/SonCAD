#ifndef _Workspace_h_
#define _Workspace_h_

#include <vector>

#include <boost/signals2.hpp>

#include <AIS_InteractiveContext.hxx>
#include <gp_Pln.hxx>
#include <Standard_Transient.hxx>
#include <V3d_Viewer.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_DirectionalLight.hxx>
#include <V3d_AmbientLight.hxx>

// Forward declaire
class WorkingContext;
class Document;
class Viewport;

DEFINE_STANDARD_HANDLE(Workspace, Standard_Transient)

class Workspace final : public Standard_Transient
{
	using GridChangedSignal = boost::signals2::signal<void(Workspace*)>;
	using PropertyChangedSignal = boost::signals2::signal<void(const std::string&)>;

public:
	enum GridTypes
	{
		Rectangular,
		Circular
	};

public:
	explicit Workspace(const Handle(Document)& theDoc);

public:

	void InitV3dViewer(const Handle(V3d_Viewer)& theViewer);

public:
	GridChangedSignal& GridChanged()
	{
		return emit_GridChanged;
	}

private:
	void ApplyWorkingContext();

private:
	std::vector<Handle(Viewport)> myViewports;

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
	Handle(WorkingContext) myCurrentWorkingContext;

private:
	GridChangedSignal emit_GridChanged;
	PropertyChangedSignal emit_PropertyChanged;
};

#endif // !_Workspace_h_
