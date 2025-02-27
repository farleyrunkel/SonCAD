// Copyright [2024] SunCAD

#include "Core/Topology/InteractiveEntity.h"


// Constructor
InteractiveEntity::InteractiveEntity()
    : Entity(), _Name("Unnamed"), _IsVisible(true), _LayerId(QUuid::createUuid()) {}

// Name property
QString InteractiveEntity::GetName() const {
    return _Name;
}

void InteractiveEntity::SetName(const QString& Name) {
    //if (_name != name) {
    //    SaveUndo();
    //    _name = name;
    //    emit propertyChanged();  // Equivalent to RaisePropertyChanged
    //    if (!IsDeserializing && CoreContext::current()) {
    //        if (Document* doc = Document::current()) {
    //            doc->instanceChanged(this);
    //        }
    //    }
    //}
}

// IsVisible property
bool InteractiveEntity::IsVisible() const {
    return _IsVisible;
}

void InteractiveEntity::SetIsVisible(bool IsVisible) {
    //if (_isVisible != isVisible) {
    //    SaveUndo();
    //    _isVisible = isVisible;
    //    emit propertyChanged();
    //    if (!IsDeserializing && CoreContext::current() && CoreContext::current()->workspace()) {
    //        if (Document* doc = Document::current()) {
    //            doc->instanceChanged(this);
    //        }
    //        raiseVisualChanged();
    //    }
    //}
}

// LayerId property
QUuid InteractiveEntity::GetLayerId() const {
    return _LayerId;
}

void InteractiveEntity::SetLayerId(const QUuid& LayerId) {
    //if (_layerId != layerId) {
    //    SaveUndo();
    //    _layerId = layerId;
    //    invalidate();
    //    emit propertyChanged();
    //    emit propertyChanged("Layer");
    //    if (!IsDeserializing && CoreContext::current() && CoreContext::current()->workspace()) {
    //        raiseVisualChanged();
    //        if (Document* doc = Document::current()) {
    //            doc->instanceChanged(this);
    //        }
    //    }
    //}
}

Handle(Layer) InteractiveEntity::GetLayer() const {
    //if (CoreContext::current() && CoreContext::current()->layers()) {
    //    return CoreContext::current()->layers()->find(_layerId);
    //}
    return nullptr;
}

void InteractiveEntity::SetLayer(const Handle(Layer)& Layer) {
    //if (CoreContext::current() && CoreContext::current()->layers()) {
    //    Layer* defaultLayer = CoreContext::current()->layers()->defaultLayer();
    //    _layerId = (layer == defaultLayer || layer == nullptr) ? QUuid() : layer->guid();
    //}
}

// Invalidate method
void InteractiveEntity::Invalidate() {
    // Logic for invalidating entity
}

// Remove method
void InteractiveEntity::Remove() {
    Entity::Remove();
}

// Get transformed BRep
TopoDS_Shape InteractiveEntity::GetTransformedBRep() const {
    return TopoDS_Shape();  // Null or placeholder
}

// Raise visual changed
void InteractiveEntity::RaiseVisualChanged() {
    //if (!IsDeserializing) {
    //    emit visualChanged();
    //}
}

