// Copyright [2024] SunCAD

#ifndef SRC_IACT_WORKSPACE_MODELCONTROLLER_H_
#define SRC_IACT_WORKSPACE_MODELCONTROLLER_H_

#include <QObject>

class ModelController : public QObject {
    Q_OBJECT

public:
    explicit ModelController(QObject* parent = nullptr);;

    void dispose();

    void newModel();

    bool askForSavingModelChanges();
};

#endif // SRC_IACT_WORKSPACE_MODELCONTROLLER_H_
