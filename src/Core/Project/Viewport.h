#ifndef _Viewport_h_
#define _Viewport_h_

#include <Standard_Transient.hxx>
#include <V3d_Viewer.hxx>
#include <AIS_InteractiveContext.hxx>

#include "Core/Project/Document.h"

DEFINE_STANDARD_HANDLE(Viewport, Standard_Transient)

class Viewport final : public Standard_Transient
{
public:
	explicit Viewport() {}

private:
	Handle(Document) myDocument;
	Handle(V3d_Viewer) myViewer;
	Handle(AIS_InteractiveContext) myContext;

	bool myNeedsRedraw;
	bool myNeedsImmediateRedraw;
};

#endif // !_Viewport_h_
