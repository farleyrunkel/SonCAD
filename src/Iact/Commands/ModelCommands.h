// Copyright [2024] SonCAD

#ifndef APP_MODELCOMMANDS_H
#define APP_MODELCOMMANDS_H

#include "Pres/Commands/ActionCommand.h"
#include <QMessageBox>

class ModelCommands {
public:
    // ���徲̬�� ActiveCommand
    static const ActiveCommand CreateBox;
};

// �����ⲿ��ʼ����̬����
const ActiveCommand ModelCommands::CreateBox(
    []() {
        // ����� QMessageBox �ṩһ�����ʵĸ����ڣ����� nullptr���Լ��������Ϣ�ı�
        QMessageBox::warning(nullptr, "Create Box", "This is a warning about creating a box.");
    },
    []() {
        // �ж��Ƿ����ִ�и����� 
        return true;
    }
);

#endif  // APP_MODELCOMMANDS_H
