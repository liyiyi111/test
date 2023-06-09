#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QJsonObject>
class QThread;
class QTimer;
class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
signals:
    void deviceControl(QJsonObject obj);

protected slots:
    void socketDisconnectedSlot();
    void freeThTimerTimeoutSlot();

protected:
    void incomingConnection(qintptr socketDescriptor);
    QList<QThread *> waitForDeleteList;
    QTimer *freeThTimer;
};

#endif // MYTCPSERVER_H
