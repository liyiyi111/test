#include "zigbeeprotocol.h"
#include "zigbeedriver.h"
#include <QColor>
#include <QTimer>
ZigbeeProtocol *ZigbeeProtocol::obj=nullptr;
ZigbeeProtocol::ZigbeeProtocol(QObject *parent) : QObject(parent)
  ,sendTimer(new QTimer)
  ,requestTimer(new QTimer)
{
    connect(sendTimer, &QTimer::timeout,
            this, &ZigbeeProtocol::sendTimerTimeoutSlot);
    sendTimer->start(800);
    connect(requestTimer, &QTimer::timeout,
            this, &ZigbeeProtocol::requestTimerTimeoutSlot);
    requestTimer->start(6*1000);
    connect(ZigbeeDriver::getObject(),
            &ZigbeeDriver::receiveFromSerialPort,
            this,
            &ZigbeeProtocol::receiveFromSerialPortSlot);
}

ZigbeeProtocol *ZigbeeProtocol::getObject()
{
    if(obj == nullptr)
        obj = new ZigbeeProtocol;
    return obj;
}

bool ZigbeeProtocol::openLight1(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 11 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::openLight2(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 12 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::openLight3(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 13 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::openLight4(int light)
{
    QString cmd = "FE FE 00 FF FF 0A 10 14 ";
    unsigned char l = (unsigned int)light;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(l);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::openRGBLight(int r, int g, int b)
{
    QString cmd = "FE FE 00 FF FF 0C 10 15 ";
    unsigned char ur = (unsigned int)r;
    unsigned char ug = (unsigned int)g;
    unsigned char ub = (unsigned int)b;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ug);
    data.append(ur);
    data.append(ub);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::openRGBLight(QColor color)
{
    QString cmd = "FE FE 00 FF FF 0C 10 15 ";
    unsigned char ur = (unsigned int)color.red();
    unsigned char ug = (unsigned int)color.green();
    unsigned char ub = (unsigned int)color.blue();
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ug);
    data.append(ur);
    data.append(ub);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::alarmControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 50 21 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::alarmLedControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 50 22 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::steerengineControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 60 25 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::stepmotorControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 26 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::fanControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 27 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::relay1Control(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 28 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::relay2Control(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 70 29 ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
    addControlCmd(data);
    return true;
}

bool ZigbeeProtocol::lockControl(int status)
{
    QString cmd = "FE FE 00 FF FF 0A 80 2A ";
    unsigned char ustatus = (unsigned int)status;
    QByteArray data;
    data.append(QByteArray::fromHex(cmd.toLocal8Bit()));
    data.append(ustatus);
    data.append(
                QByteArray::fromHex(QString("FF").toLocal8Bit()));
//    return ZigbeeDriver::getObject()->sendToSerialPort(data);
    addControlCmd(data);
    return true;
}

void ZigbeeProtocol::requestCo2()
{
    QString cmd = "FE FE 00 FF FF 09 20 16 FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

int ZigbeeProtocol::getCo2()
{
    return co2;
}

void ZigbeeProtocol::requestUv()
{
    QString cmd = "FE FE 00 FF FF 09 20 17 FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

int ZigbeeProtocol::getUv()
{
    return uv;
}

void ZigbeeProtocol::requestTe()
{
    QString cmd = "FE FE 00 FF FF 09 20 18 FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

double ZigbeeProtocol::getTe()
{
    return te;
}

void ZigbeeProtocol::requestHu()
{
    QString cmd = "FE FE 00 FF FF 09 20 19 FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

double ZigbeeProtocol::getHu()
{
    return hu;
}

void ZigbeeProtocol::requestLight()
{
    QString cmd = "FE FE 00 FF FF 09 20 2C FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

int ZigbeeProtocol::getLight()
{
    return light;
}

void ZigbeeProtocol::requestMq5()
{
    QString cmd = "FE FE 00 FF FF 09 30 1A FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

bool ZigbeeProtocol::getMq5()
{
    return mq5;
}

void ZigbeeProtocol::requestFire()
{
    QString cmd = "FE FE 00 FF FF 09 30 1B FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

bool ZigbeeProtocol::getFire()
{
    return fire;
}

void ZigbeeProtocol::requestMq2()
{
    QString cmd = "FE FE 00 FF FF 09 30 1C FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

bool ZigbeeProtocol::getMq2()
{
    return mq2;
}

void ZigbeeProtocol::requestInf()
{
    QString cmd = "FE FE 00 FF FF 09 30 1D FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

bool ZigbeeProtocol::getInf()
{
    return inf;
}

void ZigbeeProtocol::requestPm25()
{
    QString cmd = "FE FE 00 FF FF 09 40 1E FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

int ZigbeeProtocol::getPm25()
{
    return pm2_5;
}

void ZigbeeProtocol::requestTe2()
{
    QString cmd = "FE FE 00 FF FF 09 40 1F FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

double ZigbeeProtocol::getTe2()
{
    return te2;
}

void ZigbeeProtocol::requestHu2()
{
    QString cmd = "FE FE 00 FF FF 09 40 20 FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

double ZigbeeProtocol::getHu2()
{
    return hu2;
}

void ZigbeeProtocol::requestDS()
{
    QString cmd = "FE FE 00 FF FF 09 50 23 FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

bool ZigbeeProtocol::getDS()
{
    return DS;
}

void ZigbeeProtocol::requestFS()
{
    QString cmd = "FE FE 00 FF FF 09 50 24 FF";
    addSensorRequestCmd(QByteArray::fromHex(cmd.toLocal8Bit()));
}

bool ZigbeeProtocol::getFS()
{
    return FS;
}

void ZigbeeProtocol::sendTimerTimeoutSlot()
{
    if(dataList.isEmpty())
        return;
    bool ok = ZigbeeDriver::getObject()
            ->sendToSerialPort(dataList.first());
    if(ok)
        dataList.removeFirst();
}

void ZigbeeProtocol::requestTimerTimeoutSlot()
{
    requestCo2();
    requestUv();
    requestTe();
    requestHu();
    requestLight();
    requestMq5();
    requestFire();
    requestMq2();
    requestInf();
    requestPm25();
    requestTe2();
    requestHu2();
    requestDS();
    requestFS();
}

void ZigbeeProtocol::receiveFromSerialPortSlot(const QByteArray &data)
{
    dataAll.append(data);
    if(dataAll.length() < 9)
        return;
    for(int i=1;i<dataAll.length();i++)
    {
        //帧头
        if((unsigned char)dataAll.at(i) == 0xEF &&
                (unsigned char)dataAll.at(i-1)==0xEF)
        {
            //i==1
            if(i != 1)
            {
                dataAll = dataAll.mid(i-1);
                i=1;
            }
            //桢长度
            int dataLen = dataAll.length();
            if(dataLen < 9)
                return;
            unsigned int len = (unsigned char)dataAll.at(5);
            if(dataLen > 11)
            {
                //数据有问题
                dataAll = dataAll.mid(1);
                i=0;
                continue;
            }
            if(dataLen < len)
                return;
            //帧尾
            if((unsigned char)dataAll.at(len-1) != 0xFF)
            {
                //数据有问题
                dataAll = dataAll.mid(1);
                i=0;
                continue;
            }
            else
            {
                QByteArray frame = dataAll.mid(0, len);
                handleFrame(frame);
                if(frame.length() == dataAll.length()){
                    dataAll.clear();
                    return;
                }
                dataAll = dataAll.mid(len);
                i=0;
                continue;
            }
        }
    }
}

void ZigbeeProtocol::addControlCmd(QByteArray cmd)
{
    dataList.insert(0, cmd);
}

void ZigbeeProtocol::addSensorRequestCmd(QByteArray cmd)
{
    dataList.append(cmd);
}

void ZigbeeProtocol::handleFrame(const QByteArray &data)
{
    unsigned int deviceId = (unsigned char)data.at(7);
    if(deviceId == 0x16)
    {//co2
        co2 = (unsigned char)data.at(8) |
                (unsigned char)data.at(9)<<8;
    }
    else if(deviceId == 0x17)
    {
        uv = (unsigned char)data.at(8) |
                (unsigned char)data.at(9)<<8;
    }
    else if(deviceId == 0x18)
    {
//        te = (unsigned char)data.at(8) |
//                (unsigned char)data.at(9)<<8;
        int zs = (unsigned char)data.at(8);
        double xs = (double)(unsigned char)data.at(9)/100.0;
        te = zs+xs;
    }
    else if(deviceId == 0x19)
    {
        int zs = (unsigned char)data.at(8);
        double xs = (double)(unsigned char)data.at(9)/100.0;
        hu = zs+xs;
    }
    else if(deviceId == 0x2C)
    {
        light = (unsigned char)data.at(8) |
                (unsigned char)data.at(9)<<8;
    }
    else if(deviceId == 0x1A)
    {
        if((unsigned char)data.at(8)==0x01)
        {
            mq5=true;
        }
        else
            mq5=false;
    }
    else if(deviceId == 0x1B)
    {
        if((unsigned char)data.at(8)==0x01)
        {
            fire=true;
        }
        else
            fire=false;
    }
    else if(deviceId == 0x1C)
    {
        if((unsigned char)data.at(8)==0x01)
        {
            mq2=true;
        }
        else
            mq2=false;
    }
    else if(deviceId == 0x1D)
    {
        if((unsigned char)data.at(8)==0x01)
        {
            inf=true;
        }
        else
            inf=false;
    }
    else if(deviceId == 0x1E)
    {
        pm2_5 = (unsigned char)data.at(8) |
                (unsigned char)data.at(9)<<8;
    }
    else if(deviceId == 0x1F)
    {
        int zs = (unsigned char)data.at(8);
        double xs = (double)(unsigned char)data.at(9)/100.0;
        te2 = zs+xs;
    }
    else if(deviceId == 0x20)
    {
        int zs = (unsigned char)data.at(8);
        double xs = (double)(unsigned char)data.at(9)/100.0;
        hu2 = zs+xs;
    }
    else if(deviceId == 0x23)
    {
        if((unsigned char)data.at(8)==0x01)
        {
            DS=true;
        }
        else
            DS=false;
    }
    else if(deviceId == 0x24)
    {
        if((unsigned char)data.at(8)==0x01)
        {
            FS=true;
        }
        else
            FS=false;
    }


}
