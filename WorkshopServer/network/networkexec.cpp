#include "networkexec.h"
#include "mytcpserver.h"
#include "configexec.h"
NetworkExec *NetworkExec::obj = nullptr;
NetworkExec::NetworkExec(QObject *parent)
    : QObject{parent}
    , userServer(new MyTcpServer)
{
}

NetworkExec *NetworkExec::getObject()
{
    if(obj == nullptr)
        obj = new NetworkExec;
    return obj;
}

void NetworkExec::startServer()
{
    if(userServer->isListening())
        userServer->close();
    int port;
    bool ok =
        ConfigExec::getObject()
            ->getNetConfig(port);
    if(!ok)
        return;
    userServer->listen(QHostAddress::Any,
                       port);
}






