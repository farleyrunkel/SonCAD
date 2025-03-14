// Copyright [2024] SunCAD

#ifndef COMM_UTILS_H_
#define COMM_UTILS_H_

#include <memory>

#include <Message.hxx>
#include <Message_Messenger.hxx>
#include <Message_PrinterOStream.hxx>
#include <OSD_Path.hxx>
#include <Standard_CString.hxx>

class Utils
{
public:
	static void RedirectOCCTMessagesToFile(const Standard_CString& filePath, Standard_Boolean append = Standard_True)
    {
        // 获取全局消息管理器
        Handle(Message_Messenger) messenger = Message::DefaultMessenger();

        // 清空默认打印器（可选，避免控制台输出）
        messenger->RemovePrinters(STANDARD_TYPE(Message_PrinterOStream));

        // 创建文件打印器
        Handle(Message_PrinterOStream) filePrinter = new Message_PrinterOStream(filePath, append);
        if(!filePrinter->GetStream().good())
        {
            std::cerr << "无法打开文件: " << filePath << std::endl;
            return;
        }

        // 注册到消息管理器
        messenger->AddPrinter(filePrinter);

        // 测试消息
        Message::SendInfo() << "日志已重定向到 " << filePath;
    }
};

#endif  // COMM_UTILS_H_
