#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);

signals:
protected slots:
    //void readyReadSlot();
public slots:
};

#endif // MYTCPSOCKET_H
