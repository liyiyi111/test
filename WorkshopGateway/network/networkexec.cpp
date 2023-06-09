#include "networkexec.h"
#include <QTcpSocket>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QString>
#include <QJsonArray>
#include <QByteArray>
#include <QDebug>
NetworkExec *NetworkExec::obj = nullptr;
NetworkExec::NetworkExec(QObject *parent) : QObject(parent)
  ,client(new QTcpSocket)
{
    connect(client, &QTcpSocket::readyRead,
            this, &NetworkExec::clientReadyReadSlot);
    client->connectToHost("127.0.0.1",20001);
    client->waitForConnected(2000);
}
NetworkExec *NetworkExec::getObject()
{
    if(obj == nullptr)
        obj = new NetworkExec;
    return obj;
}

void NetworkExec::deviceLogin(QString index, QString password)
{
    QJsonObject obj;
    obj.insert("type", 8000);
    obj.insert("index", index);
    obj.insert("password", password);
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

void NetworkExec::handleFrame(const QByteArray &frame)
{
    QJsonObject obj = QJsonDocument::fromJson(frame)
            .object();
    int type = obj.value("type").toInt();
    if(type == 8001)
    {
       QString index = obj.value("index").toString();
       bool re = obj.value("re").toBool();
       int error_id = obj.value("error_id").toInt();
       QString identification = obj.value("identification").toString();
       QString time = obj.value("time").toString();
       emit deviceLoginRe(index,re,error_id,identification,time);
    }
    else if(type == 2001)
    {
        QString index = obj.value("index").toString();
        int id = obj.value("id").toInt();
        int brightness = obj.value("brightness").toInt();
        emit openLightSig(index,id,brightness);
    }
    else if(type == 2002)
    {
        QString index = obj.value("index").toString();
        int r = obj.value("r").toInt();
        int g = obj.value("g").toInt();
        int b = obj.value("b").toInt();
        emit openRGBLightSig(index, r, g, b);
    }
    else if(type == 2003)
    {
        QString index = obj.value("index").toString();
        int id = obj.value("id").toInt();
        bool sw = obj.value("sw").toBool();
        emit openDevice1To8Re(index, id, sw);
    }


}
