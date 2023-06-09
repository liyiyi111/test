#include "mainpage.h"
#include "ui_mainpage.h"
#include "zigbeedriver.h"
#include "zigbeeprotocol.h"
#include "networkexec.h"
#include <QMessageBox>
#include <QByteArray>
#include <QComboBox>
#include <QColorDialog>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
  ,receiveTimer(new QTimer)
  ,uvTimer(new QTimer)
  ,te1Timer(new QTimer)
  ,hu1Timer(new QTimer)
  ,lightTimer(new QTimer)
  ,mq5Timer(new QTimer)
  ,fireTimer(new QTimer)
  ,mq2Timer(new QTimer)
  ,infTimer(new QTimer)
  ,pm25Timer(new QTimer)
  ,te2Timer(new QTimer)
  ,hu2Timer(new QTimer)
  ,DSTimer(new QTimer)
  ,FSTimer(new QTimer)
  ,start(new QTimer)
  , client(new QTcpSocket)
{
    ui->setupUi(this);
    ui->cbPortName->addItems(ZigbeeDriver::getObject()->getSerialPortList());
    connect(receiveTimer, &QTimer::timeout,
            this, &MainPage::receiveTimerTimeoutSlot);
    connect(uvTimer, &QTimer::timeout,
            this, &MainPage::uvTimerTimeoutSlot);
    connect(te1Timer, &QTimer::timeout,
            this, &MainPage::te1TimerTimeoutSlot);
    connect(hu1Timer, &QTimer::timeout,
            this, &MainPage::hu1TimerTimeoutSlot);
    connect(lightTimer, &QTimer::timeout,
            this, &MainPage::lightTimerTimeoutSlot);
    connect(mq5Timer, &QTimer::timeout,
            this, &MainPage::mq5TimerTimeoutSlot);
    connect(fireTimer, &QTimer::timeout,
            this, &MainPage::fireTimerTimeoutSlot);
    connect(mq2Timer, &QTimer::timeout,
            this, &MainPage::mq2TimerTimeoutSlot);
    connect(infTimer, &QTimer::timeout,
            this, &MainPage::infTimerTimeoutSlot);
    connect(pm25Timer, &QTimer::timeout,
            this, &MainPage::pm25TimerTimeoutSlot);
    connect(te2Timer, &QTimer::timeout,
            this, &MainPage::te2TimerTimeoutSlot);
    connect(hu2Timer, &QTimer::timeout,
            this, &MainPage::hu2TimerTimeoutSlot);
    connect(DSTimer, &QTimer::timeout,
            this, &MainPage::DSTimerTimeoutSlot);
    connect(FSTimer, &QTimer::timeout,
            this, &MainPage::FSTimerTimeoutSlot);
    connect(start, &QTimer::timeout,
            this, &MainPage::startTimerTimeoutSlot);
    NetworkExec *exec = NetworkExec::getObject();
    connect(exec, &NetworkExec::deviceLoginRe,
            this, &MainPage::deviceLoginSlot);
    connect(exec, &NetworkExec::openLightSig,
            this, &MainPage::openLightSlot);
    connect(exec, &NetworkExec::openRGBLightSig,
            this, &MainPage::openRGBLightSlot);
    connect(exec, &NetworkExec::openDevice1To8Re,
            this, &MainPage::openDevice1To8Slot);
    client->connectToHost("127.0.0.1",20001);
    client->waitForConnected(2000);


}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::receiveTimerTimeoutSlot()
{
    int co2 = ZigbeeProtocol::getObject()->getCo2();
//    QString temp =
//        QString("[%1]->:CO2:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(co2);
//    ui->tbShow->append(temp);
    ui->btnGetCo2->setText(QString("co2(%1)")
                           .arg(co2));
    //qDebug()<<"adad";
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 11);
//    obj.insert("co2", ZigbeeProtocol::getObject()->getCo2());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::uvTimerTimeoutSlot()
{
    int uv = ZigbeeProtocol::getObject()->getUv();
    ui->btnGetUv->setText(QString("紫外线(%1)")
                           .arg(uv));
//    QString temp =
//        QString("[%1]->:uv:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(uv);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 12);
//    obj.insert("uv", ZigbeeProtocol::getObject()->getUv());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::te1TimerTimeoutSlot()
{
    double te1 = ZigbeeProtocol::getObject()->getTe();
    ui->btnGetTe1->setText(QString("温度1(%1)")
                           .arg(te1));
//    QString temp =
//        QString("[%1]->:te1:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(te1);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 13);
//    obj.insert("te1", ZigbeeProtocol::getObject()->getTe());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::hu1TimerTimeoutSlot()
{
    double hu1 = ZigbeeProtocol::getObject()->getHu();
    ui->btnGethu1->setText(QString("湿度1(%1)")
                           .arg(hu1));
//    QString temp =
//        QString("[%1]->:hu1:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(hu1);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 14);
//    obj.insert("hu1", ZigbeeProtocol::getObject()->getHu());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::lightTimerTimeoutSlot()
{
    int light = ZigbeeProtocol::getObject()->getLight();
    ui->btnGetLight->setText(QString("光照(%1)")
                           .arg(light));
//    QString temp =
//        QString("[%1]->:light:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(light);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 15);
//    obj.insert("light", ZigbeeProtocol::getObject()->getLight());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::mq5TimerTimeoutSlot()
{
    QString data;
    bool mq5 = ZigbeeProtocol::getObject()->getMq5();
    if(!mq5)
    {
        data="异常";
    }
    else
        data="正常";
    ui->btnGetmq5->setText(QString("甲烷(%1)")
                           .arg(data));
//    QString temp =
//        QString("[%1]->:mq5:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(data);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 16);
//    obj.insert("mq5", ZigbeeProtocol::getObject()->getMq5());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::fireTimerTimeoutSlot()
{
    QString data;
    bool fire = ZigbeeProtocol::getObject()->getFire();
    if(!fire)
        data="异常";
    else
        data="正常";
    ui->btnGetFire->setText(QString("火光(%1)")
                           .arg(data));
//    QString temp =
//        QString("[%1]->:fire:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(data);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 17);
//    obj.insert("fire", ZigbeeProtocol::getObject()->getFire());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::mq2TimerTimeoutSlot()
{
    QString data;
    bool mq2 = ZigbeeProtocol::getObject()->getMq2();
    if(!mq2)
        data="异常";
    else
        data="正常";
    ui->btnGetMq2->setText(QString("烟雾(%1)")
                           .arg(data));
//    QString temp =
//        QString("[%1]->:mq2:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(data);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 18);
//    obj.insert("mq2", ZigbeeProtocol::getObject()->getMq2());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::infTimerTimeoutSlot()
{
    QString data;
    bool inf = ZigbeeProtocol::getObject()->getInf();
    if(!inf)
        data="异常";
    else
        data="正常";
    ui->btnGetInf->setText(QString("红外(%1)")
                           .arg(data));
//    QString temp =
//        QString("[%1]->:inf:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(data);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 18);
//    obj.insert("inf", ZigbeeProtocol::getObject()->getInf());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::pm25TimerTimeoutSlot()
{
    int pm25 = ZigbeeProtocol::getObject()->getPm25();
    ui->btnGetPm25->setText(QString("pm2.5(%1)")
                           .arg(pm25));
//    QString temp =
//        QString("[%1]->:pm2.5:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(pm25);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 19);
//    obj.insert("pm25", ZigbeeProtocol::getObject()->getPm25());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::te2TimerTimeoutSlot()
{
    double te2 = ZigbeeProtocol::getObject()->getTe2();
    ui->btnGetTe2->setText(QString("温度2(%1)")
                           .arg(te2));
//    QString temp =
//        QString("[%1]->:te2:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(te2);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 20);
//    obj.insert("te2", ZigbeeProtocol::getObject()->getTe2());
//    client->write(QJsonDocument(obj).toJson());
}

void MainPage::hu2TimerTimeoutSlot()
{
    double hu2 = ZigbeeProtocol::getObject()->getHu2();
    ui->btnGetHu2->setText(QString("湿度2(%1)")
                           .arg(hu2));
//    QString temp =
//        QString("[%1]->:hu2:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(hu2);
//    ui->tbShow->append(temp);
//    if(client->state() != QTcpSocket::ConnectedState)
//        return;
//    QJsonObject obj;
//    obj.insert("type", 1001);
//    obj.insert("identification", 1);
//    obj.insert("index", 21);
//    obj.insert("hu2", ZigbeeProtocol::getObject()->getHu2());
    //    client->write(QJsonDocument(obj).toJson());
}

void MainPage::DSTimerTimeoutSlot()
{
    QString data;
    bool DS = ZigbeeProtocol::getObject()->getDS();
    if(!DS)
        data="异常";
    else
        data="正常";
    ui->btnDS->setText(QString("对射(%1)")
                           .arg(data));
//    QString temp =
//        QString("[%1]->:hu2:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(DS);
//    ui->tbShow->append(temp);
}

void MainPage::FSTimerTimeoutSlot()
{
    QString data;
    bool FS = ZigbeeProtocol::getObject()->getFS();
    if(!FS)
        data="异常";
    else
        data="正常";
    ui->btnFS->setText(QString("反射(%1)")
                           .arg(data));
//    QString temp =
//        QString("[%1]->:hu2:%2")
//        .arg(QDateTime::currentDateTime()
//             .toString("yyyy-MM-dd hh:mm:ss"))
//        .arg(FS);
//    ui->tbShow->append(temp);
}

void MainPage::startTimerTimeoutSlot()
{
    if(client->state() != QTcpSocket::ConnectedState)
        return;
    QJsonObject obj;
    obj.insert("type", 1001);
    obj.insert("index", Index);
    obj.insert("identification",Identification);
    obj.insert("co2", ZigbeeProtocol::getObject()->getCo2());
    obj.insert("uv", ZigbeeProtocol::getObject()->getUv());
    obj.insert("te1", ZigbeeProtocol::getObject()->getTe());
    obj.insert("hu1", ZigbeeProtocol::getObject()->getHu());
    obj.insert("light", ZigbeeProtocol::getObject()->getLight());
    obj.insert("mq5", ZigbeeProtocol::getObject()->getMq5());
    obj.insert("fire", ZigbeeProtocol::getObject()->getFire());
    obj.insert("mq2", ZigbeeProtocol::getObject()->getMq2());
    obj.insert("inf", ZigbeeProtocol::getObject()->getInf());
    obj.insert("pm25", ZigbeeProtocol::getObject()->getPm25());
    obj.insert("te2", ZigbeeProtocol::getObject()->getTe2());
    obj.insert("hu2", ZigbeeProtocol::getObject()->getHu2());
    obj.insert("DS", ZigbeeProtocol::getObject()->getDS());
    obj.insert("FS", ZigbeeProtocol::getObject()->getFS());
    client->write(QJsonDocument(obj).toJson());
//    QByteArray arr= QJsonDocument(obj).toJson();
    ui->tbShow->append(QString("[%1]->%2")
                .arg(QDateTime::currentDateTime()
                     .toString("yyyy-MM-dd hh:mm:ss"))
                            .arg(QString(QJsonDocument(obj).toJson())));

}

void MainPage::deviceLoginSlot(QString index, bool re, int error_id, QString identification, QString time)
{
    Re = re;
    Index=index;
    if(re==true)
    {     
        Identification=identification;
        ui->tbShow->setText("设备请求登录成功");
        //start->start(3000);
    }
    else if(re==false)
    {
        //start->stop();
    }

}

void MainPage::openLightSlot(QString index, int id, int brightness)
{
    if(Re == true)
    {
        if(id == 1)
            ZigbeeProtocol::getObject()->openLight1(brightness);
        else if(id == 2)
            ZigbeeProtocol::getObject()->openLight2(brightness);
        else if(id == 3)
            ZigbeeProtocol::getObject()->openLight3(brightness);
        else if(id == 4)
            ZigbeeProtocol::getObject()->openLight4(brightness);
    }

}

void MainPage::openRGBLightSlot(QString index, int r, int g, int b)
{
    if(Re == true)
    {
        ZigbeeProtocol::getObject()->openRGBLight(r, g, b);
    }

}

void MainPage::openDevice1To8Slot(QString index, int id, bool sw)
{
    int status;
    if(sw==true)
        status=0x01;
    else if(sw==false)
        status=0x02;
    if(Re == true)
    {
        if(id == 1)
            ZigbeeProtocol::getObject()->alarmControl(status);
        else if(id == 2)
            ZigbeeProtocol::getObject()->alarmLedControl(status);
        else if(id == 3)
            ZigbeeProtocol::getObject()->steerengineControl(status);
        else if(id == 4)
            ZigbeeProtocol::getObject()->stepmotorControl(status);
        else if(id == 5)
            ZigbeeProtocol::getObject()->fanControl(status);
        else if(id == 6)
            ZigbeeProtocol::getObject()->relay1Control(status);
        else if(id == 7)
            ZigbeeProtocol::getObject()->relay2Control(status);
        else if(id == 8)
            ZigbeeProtocol::getObject()->lockControl(status);
    }

}

void MainPage::on_btnOpenSerial_clicked()
{
    if(ui->btnOpenSerial->text() == "打开串口"){
        if(!ZigbeeDriver::getObject()->openSerialPort(ui->cbPortName->currentText(),ui->cbBaudRate->currentText().toUInt()))
        {
            QMessageBox::warning(this,
                                 "警告",
                                 "抱歉串口没打开");
        }
        else{
            ui->btnOpenSerial->setText("关闭串口");
        }


    }
    else if(ui->btnOpenSerial->text() == "关闭串口"){
        ZigbeeDriver::getObject()->closeSerialPort();
        ui->btnOpenSerial->setText("打开串口");
    }



}

//void MainPage::on_btnSend_clicked()
//{
//    QString data = ui->leText->text();
//    QByteArray Data;
//    Data = data.toLocal8Bit();
//    if(!ZigbeeDriver::getObject()->sendToSerialPort(Data))
//    {
//        QMessageBox::warning(this,
//                             "警告",
//                             "发送失败");
//    }
//}

void MainPage::on_hsLight3_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight3(ui->hsLight3->value());
}

void MainPage::on_hsLight1_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight1(ui->hsLight1->value());
}

void MainPage::on_hsLight2_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight2(ui->hsLight2->value());
}

void MainPage::on_hsLight4_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight4(ui->hsLight4->value());
}

void MainPage::on_btnAlarmOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmControl(1);
}

void MainPage::on_btnAlarmClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmControl(2);
}

void MainPage::on_btnAlarmLedOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmLedControl(1);
}

void MainPage::on_btnAlarmLedClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmLedControl(2);
}

void MainPage::on_btnSteerengineOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->steerengineControl(1);
}

void MainPage::on_btnSteerengineClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->steerengineControl(2);
}

void MainPage::on_btnStepmotorOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->stepmotorControl(1);
}

void MainPage::on_btnStepmotorClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->stepmotorControl(2);
}

void MainPage::on_btnFanOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->fanControl(1);
}

void MainPage::on_btnFanClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->fanControl(2);
}

void MainPage::on_btnRelay1Open_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay1Control(1);
}

void MainPage::on_btnRelay1Close_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay1Control(2);
}

void MainPage::on_btnRelay2Open_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay2Control(1);
}

void MainPage::on_btnRelay2Close_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay2Control(2);
}

void MainPage::on_btnLockOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->lockControl(1);
}

void MainPage::on_btnLockClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->lockControl(2);
}

void MainPage::on_btnColor_clicked()
{
    auto color = QColorDialog::getColor(Qt::black,this,"颜色");
    ZigbeeProtocol::getObject()
            ->openRGBLight(color);
}

void MainPage::on_btnGetCo2_clicked()
{
    receiveTimer->start(2000);
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();


}

void MainPage::on_btnGetUv_clicked()
{
//    receiveTimer->stop();
    uvTimer->start(2000);
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetTe1_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
    te1Timer->start(2000);
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGethu1_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
    hu1Timer->start(2000);
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetLight_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
    lightTimer->start(2000);
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetmq5_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
    mq5Timer->start(2000);
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetFire_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
    fireTimer->start(2000);
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetMq2_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
    mq2Timer->start(2000);
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetInf_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
    infTimer->start(2000);
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetPm25_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
    pm25Timer->start(2000);
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetTe2_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
    te2Timer->start(2000);
//    hu2Timer->stop();
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetHu2_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
    hu2Timer->start(2000);
//    DSTimer->stop();
//    FSTimer->stop();
}

void MainPage::on_btnGetData_clicked()
{
    NetworkExec::getObject()->deviceLogin(ui->leDeviceId->text(),ui->leDevicePassword->text());
}

void MainPage::on_btnUploadData_clicked()
{
    if(client->state() == QAbstractSocket::UnconnectedState)
    {
        ui->tbShow->append("与服务器断开，无法上传数据");
        return;
    }
    if(Re==true)
    {
        start->start(5000);
    }
}

void MainPage::on_btnDS_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
    DSTimer->start(2000);
//    FSTimer->stop();
}

void MainPage::on_btnFS_clicked()
{
//    receiveTimer->stop();
//    uvTimer->stop();
//    te1Timer->stop();
//    hu1Timer->stop();
//    lightTimer->stop();
//    mq5Timer->stop();
//    fireTimer->stop();
//    mq2Timer->stop();
//    infTimer->stop();
//    pm25Timer->stop();
//    te2Timer->stop();
//    hu2Timer->stop();
//    DSTimer->stop();
    FSTimer->start(2000);
}

void MainPage::on_btnClearData_clicked()
{
    ui->tbShow->clear();
}
