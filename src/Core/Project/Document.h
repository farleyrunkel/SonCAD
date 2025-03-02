// Copyright [2024] SunCAD

#ifndef _Document_H_
#define _Document_H_

#include <TDocStd_Document.hxx>
#include <TCollection_ExtendedString.hxx>

DEFINE_STANDARD_HANDLE(Document, TDocStd_Document)

class Document : public TDocStd_Document
{
public:
    Document(const TCollection_ExtendedString& astorageformat) 
        : TDocStd_Document(astorageformat) {}
};

#endif  // _Document_H_
