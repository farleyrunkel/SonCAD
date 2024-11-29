// Copyright [2024] SunCAD

#ifndef SRC_CORE_TOPOLOGY_LAYER_H_
#define SRC_CORE_TOPOLOGY_LAYER_H_

#include <QObject>
#include <QString>
#include <QColor>
#include <limits>
#include <memory>

#include <Standard_Transient.hxx>
#include <Standard_Handle.hxx>

#include "Core/Topology/Entity.h"

class SerializationContext;

DEFINE_STANDARD_HANDLE(Sun_Layer, Standard_Transient);

class Sun_Layer : public Sun_Entity
{
    Q_OBJECT
    Q_PROPERTY(QString name READ Name WRITE SetName NOTIFY NameChanged)
    Q_PROPERTY(bool isVisible READ IsVisible WRITE SetIsVisible NOTIFY VisibilityChanged)
    Q_PROPERTY(bool isLocked READ IsLocked WRITE SetIsLocked NOTIFY LockStatusChanged)
    Q_PROPERTY(QColor color READ Color WRITE SetColor NOTIFY ColorChanged)
    Q_PROPERTY(float transparency READ Transparency WRITE SetTransparency NOTIFY TransparencyChanged)

public:
    explicit Sun_Layer(QObject* parent = nullptr);

    // Name Property
    QString Name() const;
    void SetName(const QString& value);

    // Visibility Property
    bool IsVisible() const;
    void SetIsVisible(bool value);

    // Lock Status Property
    bool IsLocked() const {
        return _isLocked;
    }
    void SetIsLocked(bool value);

    // Color Property
    QColor Color() const;
    void SetColor(const QColor& value);

    // Transparency Property
    float Transparency() const;
    void SetTransparency(float value);

signals:
    void NameChanged(const QString&);
    void VisibilityChanged(bool);
    void LockStatusChanged(bool);
    void ColorChanged(const QColor&);
    void TransparencyChanged(float);

private:
    QString _name;
    bool _isVisible = true;
    bool _isLocked = false;
    QColor _color = QColor(Qt::white);
    float _transparency = 0.0f;
};

#endif  // SRC_CORE_TOPOLOGY_LAYER_H_
