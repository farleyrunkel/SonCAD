#ifndef INTF_ICOMMAND_H
#define INTF_ICOMMAND_H

class ICommand {
public:
    virtual ~ICommand() = default;

    // 执行命令
    virtual void execute() = 0;

    // 检查命令是否可以执行
    virtual bool canExecute() const = 0;
};

#endif // INTF_ICOMMAND_H
