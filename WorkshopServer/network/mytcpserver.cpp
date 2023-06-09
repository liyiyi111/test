#include "mytcpserver.h"
#include <QThread>
#include "mytcpsocket.h"
#include <QTimer>
#include <QTime>

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
    , freeThTimer(new QTimer)
{
    connect(freeThTimer,
            &QTimer::timeout,
            this,
            &MyTcpServer::freeThTimerTimeoutSlot);
    freeThTimer->start(5000);
    srand(QTime::currentTime().toString("sszzz").toInt());
}

void MyTcpServer::socketDisconnectedSlot()
{
    MyTcpSocket *socket = qobject_cast<MyTcpSocket *>
            (sender());
    disconnect(socket, nullptr, nullptr, nullptr);
    disconnect(this, nullptr, socket, nullptr);
    QThread *th = socket->thread();
    socket->deleteLater();
    th->quit();
    waitForDeleteList.append(th);
}

void MyTcpServer::freeThTimerTimeoutSlot()
{
    for(int i = 0; i < waitForDeleteList.length();
        i++)
    {
        QThread *th = waitForDeleteList.at(i);
        if(th->isFinished())
        {
            waitForDeleteList.removeOne(th);
            th->deleteLater();
            i--;
            continue;
        }
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    MyTcpSocket *socket = new MyTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    //绑定
    connect(socket, &MyTcpSocket::disconnected,
            this, &MyTcpServer::socketDisconnectedSlot);
    connect(socket, &MyTcpSocket::deviceControl,
            this, &MyTcpServer::deviceControl);
    connect(this, &MyTcpServer::deviceControl,
            socket, &MyTcpSocket::serverDeviceControl);
    //创建线程
    QThread *th = new QThread;
    th->start();
    //移动
    socket->moveToThread(th);

}








