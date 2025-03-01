// Copyright [2024] SunCAD

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <map>

#include <TDocStd_Document.hxx>
#include <TDF_Label.hxx>

#include "Core/Topology/Entity.h"

DEFINE_STANDARD_HANDLE(Document, TDocStd_Document)

class Document : public TDocStd_Document
{
public:

    //! Constructs a document object defined by the
    //! string astorageformat.
    //! If a document is created outside of an application using this constructor, it must be
    //! managed by a Handle. Otherwise memory problems could appear: call of TDocStd_Owner::GetDocument
    //! creates a Handle(TDocStd_Document), so, releasing it will produce a crash.
    Standard_EXPORT Document(const TCollection_ExtendedString& astorageformat) : TDocStd_Document(astorageformat){}

private:

    std::map<TDF_Label, Handle(Entity)> _Instances;
};

#endif // DOCUMENT_H
