// Copyright [2024] SonCAD

#ifndef APP_WELCOMEDIALOG_H
#define APP_WELCOMEDIALOG_H

#include <QDialog>

class WelcomeDialog: public QDialog {
    Q_OBJECT

public:
    explicit WelcomeDialog(QWidget* parent = nullptr);
    ~WelcomeDialog() override = default;

private:
    void setupUi();;

private:

};

#endif  // APP_WELCOMEDIALOG_H
