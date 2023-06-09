#include "networkexec.h"
#include <QTcpSocket>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QDebug>
NetworkExec *NetworkExec::obj = nullptr;
NetworkExec::NetworkExec(QObject *parent)
    : QObject{parent}
    , client(new QTcpSocket)
    , stateTimer(new QTimer)
{
    connect(client, &QTcpSocket::readyRead,
            this, &NetworkExec::clientReadyReadSlot);
    connect(client, &QTcpSocket::connected,
            this, &NetworkExec::netConnected);
    connect(client, &QTcpSocket::disconnected,
            this, &NetworkExec::netDisconnected);
    connect(stateTimer, &QTimer::timeout,
            this, &NetworkExec::stateTimerTimeoutSlot);
    stateTimer->start(60 *1000);
    connectToHost();
    lastHeartTime = QDateTime::currentDateTime();
}

NetworkExec *NetworkExec::getObject()
{
    if(obj == nullptr)
        obj = new NetworkExec;
    return obj;
}

void NetworkExec::userLogin(QString username, QString password)
{
    QJsonObject obj;
    obj.insert("type", 8010);
    obj.insert("username", username);
    obj.insert("password", password);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::userRequestReal(QString index)
{
    QJsonObject obj;
    obj.insert("type", 3001);
    obj.insert("index", index);
    obj.insert("identification", checkKey);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::userRequestPast(QString index, int dataType)
{
    QJsonObject obj;
    obj.insert("type", 3002);
    obj.insert("index", index);
    obj.insert("data_type", dataType);
    obj.insert("identification", checkKey);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::userLightControl(QString index, int id, int brightness)
{
    QJsonObject obj;
    obj.insert("type", 2001);
    obj.insert("index", index);
    obj.insert("id", id);
    obj.insert("brightness", brightness);
    obj.insert("identification", checkKey);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::userColorLightControl(QString index, int r, int g, int b)
{
    QJsonObject obj;
    obj.insert("type", 2002);
    obj.insert("index", index);
    obj.insert("r", r);
    obj.insert("g", g);
    obj.insert("b", b);
    obj.insert("identification", checkKey);
    client->write(QJsonDocument(obj).toJson());
}

void NetworkExec::userDeviceControl(QString index, int id, bool sw)
{
    QJsonObject obj;
    obj.insert("type", 2003);
    obj.insert("index", index);
    obj.insert("id", id);
    obj.insert("sw", sw);
    obj.insert("identification", checkKey);
    client->write(QJsonDocument(obj).toJson());
}






void NetworkExec::clientReadyReadSlot()
{
    QByteArray data = client->readAll();
    int count = 0;
    int left = 0;
    for(int i = 0; i < data.length(); i++)
    {
        if(data.at(i) == '{'){
            if(count == 0)
            {
                left = i;
            }
            count++;
        }
        else if(data.at(i) == '}'){
            count--;
            if(count == 0)
            {
                QByteArray temp =
                    data.mid(left, i-left+1);
                handleFrame(temp);
            }
        }
    }
}

void NetworkExec::stateTimerTimeoutSlot()
{
    if(client->state() == QTcpSocket::ConnectedState){
        QJsonObject obj;
        obj.insert("type", 5000);
        client->write(QJsonDocument(obj).toJson());
        if(QDateTime::currentDateTime().toSecsSinceEpoch() - lastHeartTime.toSecsSinceEpoch() > 121)
        {
            connectToHost();
        }
    }
    else
    {
        connectToHost();
    }
}

void NetworkExec::connectToHost()
{
    client->connectToHost("127.0.0.1", 20001);
}

void NetworkExec::handleFrame(const QByteArray &frame)
{
    QJsonObject obj = QJsonDocument::fromJson(frame)
            .object();
    int type = obj.value("type").toInt();
    if(type == 8011)
    {
        bool re = obj.value("re").toBool();
        if(re)
        {
            checkKey = obj.value("identification").toString();
            //qDebug() << checkKey;
        }
        emit userLoginRe(re);
    }
    else if(type == 4001)
    {
        int index = obj.value("index").toInt();
        double te = obj.value("te").toDouble();
        double hu = obj.value("hu").toDouble();
        int co2 = obj.value("co2").toInt();
        int uv = obj.value("uv").toInt();
        int light = obj.value("light").toInt();
        int mq5 = obj.value("mq5").toInt();
        int fire = obj.value("fire").toInt();
        int mq2 = obj.value("mq2").toInt();
        int inf = obj.value("inf").toInt();
        int pm25 = obj.value("pm25").toInt();
        int DS = obj.value("DS").toInt();
        int FS = obj.value("FS").toInt();
        QString time = obj.value("time").toString();
        emit userRequestRealRe(index, te, hu, co2, uv, light, mq5, fire, mq2, inf, pm25, DS, FS, time);
    }
    else if(type == 4002)
    {
        userRequestPastRe(frame);
    }

}
