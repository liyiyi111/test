#include "mainpage.h"
#include "ui_mainpage.h"
#include <QMessageBox>
#include "networkexec.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStandardItem>
#include <QDateTime>
#include <QColorDialog>
#include <QTableView>
#include <QHeaderView>
#include <QStackedWidget>
MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
  ,t1(new QTimer)
{
    ui->setupUi(this);
    setWindowTitle("智慧车间");
    ui->lePassword->setEchoMode(QLineEdit::Password);
    ui->label_25->setStyleSheet("color: #ff9720");
   // this->setStyleSheet("QWidget{background: #e7fffe;}");
    NetworkExec* exec = NetworkExec::getObject();
    connect(exec, &NetworkExec::userLoginRe,
            this, &MainPage::userLoginSlot);
    connect(exec, &NetworkExec::userRequestRealRe,
            this, &MainPage::userRequestRealSlot);
    connect(exec, &NetworkExec::userRequestPastRe,
            this, &MainPage::userRequestPastSlot);
    connect(t1, &QTimer::timeout,
            this, &MainPage::userTimerTimeoutSlot);
    model = new QStandardItemModel(0, 6, this); // 创建模型
    model1 = new QStandardItemModel(0, 6, this);
    model2 = new QStandardItemModel(0, 6, this);
    model3 = new QStandardItemModel(0, 6, this);
    ui->tableView->horizontalHeader()->resizeSection(6, 300);
    ui->tableView->setModel(model);
    //ui->tableView->setModel(model);
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("温度")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("湿度")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("CO2"))); // 设置第 1 列的标题为 CO2
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("紫外线")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("光照")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("pm2.5")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("时间")));

    model1->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("温度")));
    model1->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("湿度")));
    model1->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("CO2"))); // 设置第 1 列的标题为 CO2
    model1->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("紫外线")));
    model1->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("光照")));
    model1->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("pm2.5")));
    model1->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("时间段")));

    model2->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("温度")));
    model2->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("湿度")));
    model2->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("CO2"))); // 设置第 1 列的标题为 CO2
    model2->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("紫外线")));
    model2->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("光照")));
    model2->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("pm2.5")));
    model2->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("时间段")));

    model3->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("温度")));
    model3->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("湿度")));
    model3->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("CO2"))); // 设置第 1 列的标题为 CO2
    model3->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("紫外线")));
    model3->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("光照")));
    model3->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("pm2.5")));
    model3->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("时间段")));
    ui->stackedWidget->setCurrentIndex(0);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::userTimerTimeoutSlot()
{
    on_btnRequestReal_clicked();
}

void MainPage::userLoginSlot(bool re)
{
    if(re)
    {
        QMessageBox::information(this,"提示","登录成功");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
        QMessageBox::warning(this, "警告", "登录失败");
}

void MainPage::userRequestRealSlot(int index, double te, double hu, int co2, int uv, int light, int mq5, int fire, int mq2, int inf, int pm25, int DS, int FS, QString time)
{
    qDebug() << index;
//    QString str = QString("设备id：%1,温度：%2,湿度：%3,co2：%4,紫外线：%5,光照：%6,pm2.5：%7,甲烷：%8,火光：%9,烟雾：%10,人体红外：%11,对射：%12,反射：%13")
//            .arg(index).arg(te).arg(hu).arg(co2).arg(uv).arg(light).arg(pm25).arg(mq5).arg(fire).arg(mq2).arg(inf).arg(DS).arg(FS);
    //ui->tbShow->append(str);
    if(mq2 == 2)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,true);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),2,true);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),5,true);
        ui->lbAlarmLight->setText("已开启");
        ui->lbAlarm->setText("已开启");
        ui->lbFan->setText("已开启");

    }
    if(mq2 == 1)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,false);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),2,false);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),5,false);
        ui->lbAlarmLight->setText("已关闭");
        ui->lbAlarm->setText("已关闭");
        ui->lbFan->setText("已关闭");

    }
    if(inf == 2)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),8,true);
        ui->lbLock->setText("已开启");
    }
    if(inf == 1)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),8,false);
        ui->lbLock->setText("已关闭");
    }
    if(fire == 2)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,true);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),2,true);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),8,true);
        ui->lbAlarmLight1->setText("已开启");
        ui->lbAlarm1->setText("已开启");
        ui->lbLock1->setText("已开启");

    }
    if(fire == 1)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,false);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),2,false);
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),8,false);
        ui->lbAlarmLight1->setText("已关闭");
        ui->lbAlarm1->setText("已关闭");
        ui->lbLock1->setText("已关闭");

    }
    if(te > 100)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,true);
        ui->lbAlarm2->setText("已开启");
    }
    if(te < 100)
    {
        NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,false);
        ui->lbAlarm2->setText("已关闭");
    }
    QList<QStandardItem*> rowItems;
    rowItems << new QStandardItem(QString::number(te));
    rowItems << new QStandardItem(QString::number(hu));
    rowItems << new QStandardItem(QString::number(co2));
    rowItems << new QStandardItem(QString::number(uv));
    rowItems << new QStandardItem(QString::number(light)); // 将 CO2 浓度添加到行数据中
    rowItems << new QStandardItem(QString::number(pm25)); // 将甲烷浓度添加到行数据中
    rowItems << new QStandardItem(time);
    model->appendRow(rowItems);
    ui->tableView->setModel(model); // 将模型绑定到 TableView 上
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑单元格
    ui->tableView->setSortingEnabled(false); // 禁止排序
}

void MainPage::userRequestPastSlot(const QByteArray &arr)
{

    QJsonObject obj = QJsonDocument::fromJson(arr)
            .object();
    QJsonArray list = obj.value("list").toArray();
    qDebug() << list;
    if(ui->leDataType->text().toInt() == 0){
        for(int i=0;i<list.size();i++)
        {

            double te = list.at(i).toObject().value("te").toDouble();
            double hu = list.at(i).toObject().value("hu").toDouble();
            int co2 = list.at(i).toObject().value("co2").toInt();
            int uv = list.at(i).toObject().value("uv").toInt();
            int light = list.at(i).toObject().value("light").toInt();
            int pm25 = list.at(i).toObject().value("pm25").toInt();
            QString time = list.at(i).toObject().value("time").toString();
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::number(te));
            rowItems << new QStandardItem(QString::number(hu));
            rowItems << new QStandardItem(QString::number(co2));
            rowItems << new QStandardItem(QString::number(uv));
            rowItems << new QStandardItem(QString::number(light)); // 将 CO2 浓度添加到行数据中
            rowItems << new QStandardItem(QString::number(pm25)); // 将甲烷浓度添加到行数据中
            rowItems << new QStandardItem(time);
            model1->appendRow(rowItems);
            ui->tableView_2->setModel(model1); // 将模型绑定到 TableView 上
            ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑单元格
            ui->tableView_2->setSortingEnabled(false); // 禁止排序


    }
    }

    if(ui->leDataType->text().toInt() == 1){
        for(int i=0;i<list.size();i++)
        {

            double te = list.at(i).toObject().value("te").toDouble();
            double hu = list.at(i).toObject().value("hu").toDouble();
            int co2 = list.at(i).toObject().value("co2").toInt();
            int uv = list.at(i).toObject().value("uv").toInt();
            int light = list.at(i).toObject().value("light").toInt();
            int pm25 = list.at(i).toObject().value("pm25").toInt();
            QString time = list.at(i).toObject().value("time").toString();
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::number(te));
            rowItems << new QStandardItem(QString::number(hu));
            rowItems << new QStandardItem(QString::number(co2));
            rowItems << new QStandardItem(QString::number(uv));
            rowItems << new QStandardItem(QString::number(light)); // 将 CO2 浓度添加到行数据中
            rowItems << new QStandardItem(QString::number(pm25)); // 将甲烷浓度添加到行数据中
            rowItems << new QStandardItem(time);
            model2->appendRow(rowItems);
            ui->tableView_3->setModel(model2); // 将模型绑定到 TableView 上
            ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑单元格
            ui->tableView_3->setSortingEnabled(false); // 禁止排序


    }
    }
    if(ui->leDataType->text().toInt() == 2){
        for(int i=0;i<list.size();i++)
        {

            double te = list.at(i).toObject().value("te").toDouble();
            double hu = list.at(i).toObject().value("hu").toDouble();
            int co2 = list.at(i).toObject().value("co2").toInt();
            int uv = list.at(i).toObject().value("uv").toInt();
            int light = list.at(i).toObject().value("light").toInt();
            int pm25 = list.at(i).toObject().value("pm25").toInt();
            QString time = list.at(i).toObject().value("time").toString();
            QList<QStandardItem*> rowItems;
            rowItems << new QStandardItem(QString::number(te));
            rowItems << new QStandardItem(QString::number(hu));
            rowItems << new QStandardItem(QString::number(co2));
            rowItems << new QStandardItem(QString::number(uv));
            rowItems << new QStandardItem(QString::number(light)); // 将 CO2 浓度添加到行数据中
            rowItems << new QStandardItem(QString::number(pm25)); // 将甲烷浓度添加到行数据中
            rowItems << new QStandardItem(time);
            model3->appendRow(rowItems);
            ui->tableView_4->setModel(model3); // 将模型绑定到 TableView 上
            ui->tableView_4->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑单元格
            ui->tableView_4->setSortingEnabled(false); // 禁止排序


        }
    }

}


void MainPage::on_btnUserLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();
    NetworkExec::getObject()->userLogin(username, password);
}

void MainPage::on_hsLight1_sliderReleased()
{
    NetworkExec::getObject()->userLightControl(ui->leIndex->text(),1,ui->hsLight1->value());
}

void MainPage::on_btnRequestReal_clicked()
{
    QString index = ui->leIndex->text();
    NetworkExec::getObject()->userRequestReal(index);
    t1->start(5000);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainPage::on_btnRequestPast_clicked()
{
    QString index = ui->leIndex->text();
    int dataType = ui->leDataType->text().toInt();
    NetworkExec::getObject()->userRequestPast(index, dataType);
    if(dataType==0)
        ui->stackedWidget_2->setCurrentIndex(1);
    else if(dataType == 1)
        ui->stackedWidget_2->setCurrentIndex(2);
    else if(dataType == 2)
        ui->stackedWidget_2->setCurrentIndex(3);
}

void MainPage::on_hsLight2_sliderReleased()
{
    NetworkExec::getObject()->userLightControl(ui->leIndex->text(),2,ui->hsLight2->value());
}

void MainPage::on_hsLight3_sliderReleased()
{
    NetworkExec::getObject()->userLightControl(ui->leIndex->text(),3,ui->hsLight3->value());
}

void MainPage::on_hsLight4_sliderReleased()
{
    NetworkExec::getObject()->userLightControl(ui->leIndex->text(),4,ui->hsLight4->value());
}

void MainPage::on_btnColorLight_clicked()
{
    auto color = QColorDialog::getColor(Qt::black,this,"颜色");
    NetworkExec::getObject()->userColorLightControl(ui->leIndex->text(),
                                                    color.red(),
                                                    color.green(),
                                                    color.blue());
}

void MainPage::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainPage::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainPage::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainPage::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainPage::on_btnAlarmOpen_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,true);
}

void MainPage::on_btnAlarmClose_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),1,false);
}

void MainPage::on_btnAlarmLedOpen_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),2,true);
}

void MainPage::on_btnAlarmLedClose_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),2,false);
}

void MainPage::on_btnSteerengineOpen_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),3,true);
}

void MainPage::on_btnSteerengineClose_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),3,false);
}

void MainPage::on_btnStepmotorOpen_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),4,true);
}

void MainPage::on_btnStepmotorClose_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),4,false);
}

void MainPage::on_btnFanOpen_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),5,true);
}

void MainPage::on_btnFanClose_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),5,false);
}

void MainPage::on_btnRelay1Open_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),6,true);
}

void MainPage::on_btnRelay1Close_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),6,false);
}

void MainPage::on_btnRelay2Open_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),7,true);
}

void MainPage::on_btnRelay2Close_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),7,false);
}

void MainPage::on_btnLockOpen_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),8,true);
}

void MainPage::on_btnLockClose_clicked()
{
    NetworkExec::getObject()->userDeviceControl(ui->leIndex->text(),8,false);
}
