// Copyright [2024] SonCAD

#ifndef SRC_CORE_APPLICATION_H_
#define SRC_CORE_APPLICATION_H_

#include <QApplication>

class Application : public QApplication {
    Q_OBJECT

 public:
    Application(int& argc, char** argv);
};

#endif  // SRC_CORE_APPLICATION_H_
