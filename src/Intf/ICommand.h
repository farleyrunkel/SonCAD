#ifndef INTF_ICOMMAND_H
#define INTF_ICOMMAND_H

class ICommand {
public:
    virtual ~ICommand() = default;

    // ִ������
    virtual void execute() = 0;

    // ��������Ƿ����ִ��
    virtual bool canExecute() const = 0;
};

#endif // INTF_ICOMMAND_H
