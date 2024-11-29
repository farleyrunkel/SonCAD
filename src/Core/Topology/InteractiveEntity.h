// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_OMTERACTIVEENTITY_H_
#define SRC_CORE_TOPOLOGY_OMTERACTIVEENTITY_H_

#include <QObject>
#include <QUuid>

#include <TopoDS_Shape.hxx>

#include "Core/Topology/Entity.h"
#include "Core/Topology/Layer.h"

class InteractiveEntity : public Sun_Entity 
{
    Q_OBJECT

public:
    explicit InteractiveEntity();

    // Name property
    QString Name() const override;
    void SetName(const QString& Name) override;

    // IsVisible property
    bool isVisible() const;
    void setIsVisible(bool isVisible);

    // LayerId property
    QUuid layerId() const;
    void setLayerId(const QUuid& layerId);

    Sun_Layer* layer() const;
    void setLayer(Sun_Layer* layer);

    // Methods
    void invalidate();
    virtual void Remove() override;
    virtual TopoDS_Shape getTransformedBRep() const;

signals:
    void visualChanged();

protected:
    void raiseVisualChanged();

private:
    QString _name;
    bool _isVisible;
    QUuid _layerId;
};

#endif  // SRC_CORE_TOPOLOGY_OMTERACTIVEENTITY_H_
