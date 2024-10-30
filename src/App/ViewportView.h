// Copyright [2024] SunCAD

#ifndef SRC_APP_VIEWPORTVIEW_H_
#define SRC_APP_VIEWPORTVIEW_H_

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

class ViewportView : public QScrollArea {
    Q_OBJECT

public:
    explicit ViewportView(QWidget* parent = nullptr);
};
#endif  // SRC_APP_VIEWPORTVIEW_H_
