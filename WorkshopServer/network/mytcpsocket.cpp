#include "mytcpsocket.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "sqlthreaddispatch.h"
#include "sqlexec.h"
#include <QJsonArray>
#include <QDateTime>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    connect(this, &MyTcpSocket::readyRead,
            this, &MyTcpSocket::readyReadSlot);
}

void MyTcpSocket::serverDeviceControl(QJsonObject obj)
{
    if(obj.value("index").toString() != deviceIndex)
        return;
    this->write(QJsonDocument(obj).toJson());
}



void MyTcpSocket::readyReadSlot()
{
    QByteArray data = this->readAll();
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

void MyTcpSocket::handleFrame(const QByteArray &frame)
{
    QJsonObject obj = QJsonDocument::fromJson(frame)
            .object();
    int type = obj.value("type").toInt();
    if(type == 8000)
    {
        handleDeviceLoginFrame(obj);
    }
    else if(type == 1001)
    {
        handleSendSenorDataFrame(obj);
    }
    else if(type == 8010)
    {
        handleUserLoginFrame(obj);
    }
    else if(type >= 2001 && type <=2003)
    {
        handleUserControlFrame(obj);
    }
    else if(type == 3001)
    {
        handleGetSenorDataFrame(obj);
    }
    else if(type == 3002)
    {
        handleGetPastDataFrame(obj);
    }
    //net->设备登录、设备传感数据获取
    //sql->设备登录、保存传感数据
}

void MyTcpSocket::handleDeviceLoginFrame(const QJsonObject &obj)
{
    QString index = obj.value("index").toString();
    QString password = obj.value("password").toString();
    SqlExec *exec = SqlThreadDispatch::getObject()
            ->getExec();
    bool ok = exec->deviceLogin(index,password);
    qDebug() << ok;
    SqlThreadDispatch::getObject()->freeExec(exec);
//    if(!ok)
//    {
//        error_id=1;
//    }

    checkKey.clear();
    for(int i = 0; i < 16; i++){
        char c;
        int n = rand() % 52;
        if(n > 25){//大写
            c = 'A' + n - 26;
        }
        else{//小写
            c = 'a' + n;
        }
        checkKey.append(c);
    }
    QJsonObject reObj;
    reObj.insert("type", 8001);
    reObj.insert("index", index);
    reObj.insert("re", ok);
    if(ok)
    {
        reObj.insert("identificaton", checkKey);
        reObj.insert("time",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        deviceIdentification = checkKey;
        deviceIndex = index;
    }
    else
    {
        reObj.insert("error_id", 1);
    }
    this->write(QJsonDocument(reObj).toJson());

}

void MyTcpSocket::handleSendSenorDataFrame(const QJsonObject &obj)
{
    int Mq5=0;
    int Fire=0;
    int Mq2=0;
    int Inf=0;
    int ds=0;
    int fs=0;
    QString index = obj.value("index").toString();
    QString identification = obj.value("identification").toString();
    int co2 = obj.value("co2").toInt();
    int uv = obj.value("uv").toInt();
    double te1 = obj.value("te1").toDouble();
    double hu1 = obj.value("hu1").toDouble();
    int light = obj.value("light").toInt();
    bool mq5 = obj.value("mq5").toBool();
    bool fire = obj.value("fire").toBool();
    bool mq2 = obj.value("mq2").toBool();
    bool inf = obj.value("inf").toBool();
    int pm25 = obj.value("pm25").toInt();
    double te2 = obj.value("te2").toDouble();
    double hu2 = obj.value("hu2").toDouble();
    bool DS = obj.value("DS").toBool();
    bool FS = obj.value("FS").toBool();
    if(mq5==true)
        Mq5=1;
    else if(mq5==false)
        Mq5=2;
    if(fire==true)
        Fire=1;
    else if(fire==false)
        Fire=2;
    if(mq2==true)
        Mq2=1;
    else if(mq2==false)
        Mq2=2;
    if(inf==true)
        Inf=1;
    else if(inf==false)
        Inf=2;
    if(DS==true)
        ds=1;
    else if(DS==false)
        ds=2;
    if(FS==true)
        fs=1;
    else if(FS==false)
        fs=2;

    if(identification!=checkKey)
        return;

    SqlExec *exec = SqlThreadDispatch::getObject()
            ->getExec();

    bool ok = exec->deviceSaveData(index,te1,hu1,co2,uv,light,pm25,Mq5,Fire,Mq2,Inf,ds,fs);
    SqlThreadDispatch::getObject()->freeExec(exec);

}

void MyTcpSocket::handleUserLoginFrame(const QJsonObject &obj)
{
    QString username = obj.value("username").toString();
    QString password = obj.value("password").toString();
    SqlExec *exec = SqlThreadDispatch::getObject()
            ->getExec();
    bool ok = exec->userLogin(username,password);
    SqlThreadDispatch::getObject()->freeExec(exec);
    userKey.clear();
    for(int i = 0; i < 16; i++){
        char c;
        int n = rand() % 52;
        if(n > 25){//大写
            c = 'A' + n - 26;
        }
        else{//小写
            c = 'a' + n;
        }
        userKey.append(c);
    }
    QJsonObject reObj;
    reObj.insert("type", 8011);
    reObj.insert("username",username);
//    reObj.insert("index", index);
    reObj.insert("re", ok);
    if(ok)
    {
        reObj.insert("identification", userKey);
        reObj.insert("time",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        userIdentification = userKey;
        userUsername = username;
    }
    else
    {
        reObj.insert("error_id", 1);
    }
    this->write(QJsonDocument(reObj).toJson());

}

void MyTcpSocket::handleUserControlFrame(const QJsonObject &obj)
{
    QString identification = obj.value("identification").toString();
    if(userIdentification != identification)
    {
        QJsonObject re;
        re.insert("type", 10000);
        re.insert("error_id", 1);
        this->write(QJsonDocument(re).toJson());
        return;
    }
    emit deviceControl(obj);
}

void MyTcpSocket::handleGetSenorDataFrame(const QJsonObject &obj)
{
    QString index = obj.value("index").toString();
    QString identification = obj.value("identification").toString();
//    if(index!=deviceIndex)
//        return;
    if(identification!=userIdentification)
        return;
    QJsonArray arr;
    SqlExec *exec = SqlThreadDispatch::getObject()
            ->getExec();
    bool ok = exec->getCurSenorData(index, arr);
    SqlThreadDispatch::getObject()->freeExec(exec);
    QJsonObject reObj;
    reObj.insert("type", 4001);
    //reObj.insert("index", index);
    foreach (QJsonValue value, arr) {
        QJsonObject obj = value.toObject();
        foreach (QString key, obj.keys()) {
                reObj.insert(key, obj.value(key));
        }
    }
    this->write(QJsonDocument(reObj).toJson());
}

void MyTcpSocket::handleGetPastDataFrame(const QJsonObject &obj)
{
    QString index = obj.value("index").toString();
    QString identification = obj.value("identification").toString();
    int data_type = obj.value("data_type").toInt();
//    if(index!=deviceIndex)
//        return;
    if(identification!=userIdentification)
        return;
    QJsonArray arr;
    SqlExec *exec = SqlThreadDispatch::getObject()
            ->getExec();
    bool ok = exec->getPastSenorData(index,data_type, arr);
    qDebug() << ok;
    SqlThreadDispatch::getObject()->freeExec(exec);
    QJsonObject reObj;
    reObj.insert("type", 4002);
    //reObj.insert("index", index);
    reObj.insert("list", arr);
    this->write(QJsonDocument(reObj).toJson());
}






