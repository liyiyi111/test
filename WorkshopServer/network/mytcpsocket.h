#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include <QJsonObject>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
public slots:
    void serverDeviceControl(QJsonObject obj);
signals:
    void deviceControl(QJsonObject obj);
protected:
    void readyReadSlot();
    void handleFrame(const QByteArray &frame);

    void handleDeviceLoginFrame(const QJsonObject &obj);
    void handleSendSenorDataFrame(const QJsonObject &obj);
    void handleUserLoginFrame(const QJsonObject &obj);
    void handleUserControlFrame(const QJsonObject &obj);
    void handleGetSenorDataFrame(const QJsonObject &obj);
    void handleGetPastDataFrame(const QJsonObject &obj);
    QString deviceIndex;
    int userId = -1;
    int clientType = -1;
    int error_id=-1;
    QString checkKey;
    QString userKey;
    QString deviceIdentification;
    QString userUsername;
    QString userIdentification;
};

#endif // MYTCPSOCKET_H
