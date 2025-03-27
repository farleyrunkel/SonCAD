// Copyright [2024] SunCAD

#include "Core/Topology/Document.h"

#include "Core/Topology/Entity.h"

//! Constructs a document object defined by the
//! string astorageformat.
//! If a document is created outside of an application using this constructor, it must be
//! managed by a Handle. Otherwise memory problems could appear: call of TDocStd_Owner::GetDocument
//! creates a Handle(TDocStd_Document), so, releasing it will produce a crash.

Document::Document(const TCollection_ExtendedString& astorageformat)
    : TDocStd_Document(astorageformat)
{}
