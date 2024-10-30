// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

#include <QObject>

#include "Aspect_NeutralWindow.hxx"
#include "Aspect_RenderingContext.hxx"
#include "Standard_Integer.hxx"

#include "Core/Viewport.h"

class ViewportController : public QObject {
    Q_OBJECT

public:
    explicit ViewportController(QObject* parent = nullptr) : QObject(parent) {}

    Viewport* viewport() const { return nullptr; }

    Handle(V3d_View) view() const {
        return this->viewport() ? this->viewport()->view() : nullptr;
    }

    const Handle(Aspect_Window)& window() const {
        return !view().IsNull() ? view()->Window() : nullptr;
    }

    void setWindow(const Handle(Aspect_Window)& theWindow,
        const Aspect_RenderingContext theContext = NULL) {
        if (!view().IsNull()) {
            view()->SetWindow(theWindow, theContext);
        }
    }

     QString dumpInfo(bool theIsBasic, bool theToPrint) {
        TCollection_AsciiString anInfo;
        if (!view().IsNull()) {
            TColStd_IndexedDataMapOfStringString aGlCapsDict;
            view()->DiagnosticInformation(aGlCapsDict, theIsBasic 
                ? Graphic3d_DiagnosticInfo_Basic 
                : Graphic3d_DiagnosticInfo_Complete);
            TColStd_IndexedDataMapOfStringString::Iterator aValueIter(aGlCapsDict);
            for (; aValueIter.More(); aValueIter.Next()) {
                if (!aValueIter.Value().IsEmpty()) {
                    if (!anInfo.IsEmpty()) {
                        anInfo += "\n";
                    }
                    anInfo += aValueIter.Key() + ": " + aValueIter.Value();
                }
            }

            if (theToPrint) {
                Message::SendInfo(anInfo);
            }
        }
        return QString::fromUtf8(anInfo.ToCString());
    }
};
#endif // SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
