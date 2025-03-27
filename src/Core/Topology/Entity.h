// Copyright [2024] SunCAD

#ifndef Entity_DOCUMENT_H
#define Entity_DOCUMENT_H

#include <boost/signals2.hpp>

#include <TDF_Label.hxx>
#include <TCollection_AsciiString.hxx>

#include "Comm/BaseObject.h"
#include "Core/Topology/Document.h"

DEFINE_STANDARD_HANDLE(Entity, BaseObject)

// Base class for Entity, assuming Entity is derived from QObject for signal/slot support
class Entity : public BaseObject
{

public:
    // Constructor
    explicit Entity();

    // Name property, virtual
	virtual TCollection_AsciiString GetName() const { return _Name; }

	virtual void SetName(const TCollection_AsciiString& value)
	{
		_Name = value;
	}

    // Error handling
	bool HasErrors() const { return _HasErrors; }

	void SetHasErrors(bool HasErrors)
	{
		if(_HasErrors != HasErrors)
		{
			_HasErrors = HasErrors;
			RaisePropertyChanged("HasErrors");
			RaiseErrorStateChanged();
		}
	}

	// Lable Property
	TDF_Label GetLabel() const { return _Label; }

	void SetLabel(const TDF_Label& value)
	{
		_Label = value;
	}

	// Document Property
	Handle(Document) GetDocument() const { return _Document; }

	void SetDocument(const Handle(Document)& value)
	{
		//_Document = value;
	}


    // Remove entity
    virtual void Remove() {
		RaiseEntityRemoved();
		_Document.Nullify();
    };

public:
    void RaiseEntityRemoved()
    {
		EntityRemoved(Handle(Entity)(this));
    }

    void RaiseErrorStateChanged()
    {
		ErrorStateChanged(Handle(Entity)(this));
    }

public:
	static boost::signals2::signal<void(const Handle(Entity)&)> EntityRemoved;
	static boost::signals2::signal<void(const Handle(Entity)&)> ErrorStateChanged;

protected:
	TDF_Label _Label;
	TCollection_AsciiString _Name;

    bool _HasErrors;
	Handle(Document) _Document;
};

#endif  // Entity_DOCUMENT_H
