// Copyright [2024] SunCAD

#ifndef SRC_CORE_PROJECT_WORKINGCONTEXT_H_
#define SRC_CORE_PROJECT_WORKINGCONTEXT_H_

#include <QObject>

class WorkingContext : public QObject {
    Q_OBJECT

public:
    explicit WorkingContext(QWidget* parent = nullptr) {};
};

#endif  // SRC_CORE_PROJECT_WORKINGCONTEXT_H_
