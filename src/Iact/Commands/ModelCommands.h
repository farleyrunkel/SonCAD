// Copyright [2024] SonCAD

#ifndef APP_MODELCOMMANDS_H
#define APP_MODELCOMMANDS_H

#include "Pres/Commands/ActionCommand.h"
#include <QMessageBox>

class ModelCommands {
public:
    // 定义静态的 ActiveCommand
    static const ActiveCommand CreateBox;
};

// 在类外部初始化静态命令
const ActiveCommand ModelCommands::CreateBox(
    []() {
        // 这里给 QMessageBox 提供一个合适的父窗口（例如 nullptr）以及标题和消息文本
        QMessageBox::warning(nullptr, "Create Box", "This is a warning about creating a box.");
    },
    []() {
        // 判断是否可以执行该命令 
        return true;
    }
);

#endif  // APP_MODELCOMMANDS_H
