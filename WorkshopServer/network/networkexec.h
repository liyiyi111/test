#ifndef NETWORKEXEC_H
#define NETWORKEXEC_H

#include <QObject>
class MyTcpServer;
/**
 * @brief 网络操作类
 */
class NetworkExec : public QObject
{
    Q_OBJECT
protected:
    explicit NetworkExec(QObject *parent = nullptr);

public:
    static NetworkExec *getObject();
    void startServer();

protected:
    static NetworkExec *obj;
    MyTcpServer *userServer;
};

#endif // NETWORKEXEC_H
