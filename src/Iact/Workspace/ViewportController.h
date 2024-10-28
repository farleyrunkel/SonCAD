// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
#define SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_

#include <QObject>

#include "Core/Viewport.h"

class ViewportController : public QObject {
    Q_OBJECT

public:
    explicit ViewportController(QObject* parent = nullptr) : QObject(parent) {}

    Viewport* viewport() { return nullptr; }
};

#endif // SRC_IACT_WORKSPACE_VIEWPORTCONTROLLER_H_
