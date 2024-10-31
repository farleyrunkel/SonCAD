// Copyright [2024] SunCAD

#include "Iact/Workspace/ViewportController.h"

inline void ViewportController::setWindow(const Handle(Aspect_Window)& theWindow, const Aspect_RenderingContext theContext) {
    if (!view().IsNull()) {
        view()->SetWindow(theWindow, theContext);
    }
}

inline QString ViewportController::dumpInfo(bool theIsBasic, bool theToPrint) {
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
