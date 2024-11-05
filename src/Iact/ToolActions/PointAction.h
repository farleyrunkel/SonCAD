// Copyright [2024] SunCAD

#ifndef SRC_IACT_TOOLACTION_POINTACTION_H_
#define SRC_IACT_TOOLACTION_POINTACTION_H_

#include "Iact/Framework/ToolAction.h"
#include <QMessageBox>
class PointAction : public ToolAction {
    Q_OBJECT

 public:
    explicit PointAction() {};
 
 protected:
    bool onStart() override {

        QMessageBox::warning(nullptr, "adsd", "dasds");
        return false;
    }

 signals:
    void preview();
    void finished();
};

#endif  // SRC_IACT_TOOLACTION_POINTACTION_H_
