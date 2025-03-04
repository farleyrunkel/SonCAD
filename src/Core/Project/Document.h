// Copyright [2024] SunCAD

#ifndef _Document_H_
#define _Document_H_

#include "Comm/BaseObject.h"

#include <TDocStd_Document.hxx>

class Document : public enable_property_changed_signal
{
public:
    Document();

private:
	Handle(TDocStd_Document) m_document;
};

#endif  // _Document_H_
