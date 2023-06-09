#include "sqlexec.h"
#include <QSqlDatabase>
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonArray>
#include "logexec.h"

SqlExec::SqlExec(QString ip, int port, QString username, QString password, QString dbName, QString connectName, QObject *parent)
    : QObject{parent}
    , db(new QSqlDatabase(
        QSqlDatabase::addDatabase(
                 "QMYSQL", connectName)))
{
    db->setHostName(ip);
    db->setPort(port);
    db->setUserName(username);
    db->setPassword(password);
    db->setDatabaseName(dbName);
    db->open();
}

bool SqlExec::getConnectState()
{
    return db->isOpen();
}

void SqlExec::setState(bool s)
{
    state = s;
}

bool SqlExec::getState()
{
    return state;
}

bool SqlExec::deviceLogin(QString deviceId, QString deviceKey)
{
    QString cmd;
    cmd = QString("SELECT * FROM `sh_device` "
                  "WHERE `device_name`='%1' AND "
                  "`device_key`='%2';")
            .arg(deviceId)
            .arg(deviceKey);
    QSqlQuery query(*db);
    bool ok = query.exec(cmd);
    if(!ok)
        return false;
    if(!query.next())
        return false;
    return true;
}

bool SqlExec::deviceSaveData(QString deviceId, double te, double hu, int co2, int uv, int light, int pm25, int mq5, int fire, int mq2, int inf, int DS, int FS)
{
    QString cmd;
    cmd = QString("INSERT INTO `sh_value` "
                  "(`device_id`,`te`,`hu`,`co2`,`uv`,`light`,`pm25`,"
                  "`fire`,`mq2`,`inf`,`mq5`,`DS`,`FS`,`time`) "
                  "VALUES('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14');")
            .arg(deviceId).arg(te).arg(hu).arg(co2).arg(uv).arg(light).arg(pm25).arg(fire)
            .arg(mq2).arg(inf).arg(mq5).arg(DS).arg(FS)
            .arg(QDateTime::currentDateTime()
                 .toString("yyyy-MM-dd hh:mm:ss"));

    QSqlQuery query(*db);
    bool ok = query.exec(cmd);
    if(!ok){
        qDebug() << cmd;
        qDebug() << query.lastError().text();
        return false;
    }

    if(query.numRowsAffected() != 1)
        return false;
    return true;
}

bool SqlExec::userLogin(QString username, QString password)
{
    QString cmd;
    cmd = QString("SELECT * FROM `sh_user` "
                  "WHERE `username`='%1' AND "
                  "`password`='%2';")
            .arg(username)
            .arg(password);
    QSqlQuery query(*db);
    bool ok = query.exec(cmd);
    if(!ok)
        return false;
    if(!query.next())
        return false;
    return true;
}

bool SqlExec::getCurSenorData(QString index, QJsonArray &arr)
{
    QString cmd;
    cmd = QString("SELECT * FROM `sh_value` "
                  "WHERE `device_id`='%1' ORDER BY `id` DESC LIMIT 1;")
            .arg(index);
    QSqlQuery query(*db);
    bool ok;
    ok = query.exec(cmd);
    if(!ok)
        return false;
    while(query.next())
    {
        QJsonObject obj;
        obj.insert("index", query.value("device_id").toInt());
        obj.insert("te", query.value("te").toDouble());
        obj.insert("hu", query.value("hu").toDouble());
        obj.insert("co2", query.value("co2").toInt());
        obj.insert("uv", query.value("uv").toInt());
        obj.insert("light", query.value("light").toInt());
        obj.insert("mq5", query.value("mq5").toInt());
        obj.insert("fire", query.value("fire").toInt());
        obj.insert("mq2", query.value("mq2").toInt());
        obj.insert("inf", query.value("inf").toInt());
        obj.insert("pm25", query.value("pm25").toInt());
        obj.insert("DS", query.value("DS").toInt());
        obj.insert("FS", query.value("FS").toInt());
        obj.insert("time", query.value("time").toString());
        arr.append(obj);
    }
    return true;
}

bool SqlExec::getPastSenorData(QString index, int data_type, QJsonArray &arr)
{
    QString cmd;
    if(data_type==0)
    {
        int count=0;
        double te=0;
        double hu=0;
        int co2=0;
        int uv=0;
        int light=0;
        int pm25=0;
        QString time;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`>=DATE_SUB(NOW(), INTERVAL 30 MINUTE);")
                .arg(index);
        QSqlQuery query(*db);
        bool ok;
        ok = query.exec(cmd);
        if(ok)
        {
            qDebug() << 0;
        }
        if(!ok)
            return false;
        if(!query.next())
            count=1;
        while(query.next())
        {
            te += query.value("te").toDouble();
            hu += query.value("hu").toDouble();
            co2 += query.value("co2").toInt();
            uv += query.value("uv").toInt();
            light += query.value("light").toInt();
            pm25 += query.value("pm25").toInt();
            count++;
        }
        QJsonObject obj;
        obj.insert("te", te/count);
        obj.insert("hu", hu/count);
        obj.insert("co2", co2/count);
        obj.insert("uv", uv/count);
        obj.insert("light", light/count);
        obj.insert("pm25", pm25/count);
        obj.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addSecs(-30*60).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj);
        qDebug() << arr;

        int count1=0;
        double te1=0;
        double hu1=0;
        int co21=0;
        int uv1=0;
        int light1=0;
        int pm251=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 30 MINUTE) AND `time`>=DATE_SUB(NOW(), INTERVAL 60 MINUTE);")
                .arg(index);
        QSqlQuery query1(*db);
        bool ok1;
        ok1 = query1.exec(cmd);
        if(!ok1)
            return false;
        if(ok1)
        {
            qDebug() << 1;
        }
        if(!query1.next())
            count1=1;
        while(query1.next())
        {
            te1 += query1.value("te").toDouble();
            hu1 += query1.value("hu").toDouble();
            co21 += query1.value("co2").toInt();
            uv1 += query1.value("uv").toInt();
            light1 += query1.value("light").toInt();
            pm251 += query1.value("pm25").toInt();
            count1++;
        }
        QJsonObject obj1;
        obj1.insert("te", te1/count1);
        obj1.insert("hu", hu1/count1);
        obj1.insert("co2", co21/count1);
        obj1.insert("uv", uv1/count1);
        obj1.insert("light", light1/count1);
        obj1.insert("pm25", pm251/count1);
        obj1.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addSecs(-30*60).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addSecs(-60*60).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj1);

        int count2=0;
        double te2=0;
        double hu2=0;
        int co22=0;
        int uv2=0;
        int light2=0;
        int pm252=0;

        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 60 MINUTE) AND `time`>=DATE_SUB(NOW(), INTERVAL 90 MINUTE);")
                .arg(index);
        QSqlQuery query2(*db);
        bool ok2;
        ok2 = query2.exec(cmd);
        if(!ok2)
            return false;
        if(ok2)
        {
            qDebug() << 2;
        }
        if(!query2.next())
            count2=1;
        while(query2.next())
        {
            te2 += query2.value("te").toDouble();
            hu2 += query2.value("hu").toDouble();
            co22 += query2.value("co2").toInt();
            uv2 += query2.value("uv").toInt();
            light2 += query2.value("light").toInt();
            pm252 += query2.value("pm25").toInt();
            count2++;
        }
        qDebug() << te2;
        QJsonObject obj2;
        obj2.insert("te", te2/count2);
        obj2.insert("hu", hu2/count2);
        obj2.insert("co2", co22/count2);
        obj2.insert("uv", uv2/count2);
        obj2.insert("light", light2/count2);
        obj2.insert("pm25", pm252/count2);
        obj2.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addSecs(-60*60).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addSecs(-90*60).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj2);
        qDebug() << arr;

//        QJsonObject obj1;
//        obj1.insert("te", te1/count);
//        obj1.insert("hu", hu1/count);
//        obj1.insert("co2", co21/count);
//        obj1.insert("uv", uv1/count);
//        obj1.insert("light", light1/count);
//        obj1.insert("pm25", pm251/count);
//        arr.append(obj1);

//        int count3=0;
//        double te3=0;
//        double hu3=0;
//        int co23=0;
//        int uv3=0;
//        int light3=0;
//        int pm253=0;

//        cmd = QString("SELECT * FROM `sh_value` "
//                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 90 MINUTE) AND `time`>=DATE_SUB(NOW(), INTERVAL 120 MINUTE);")
//                .arg(index);
//        QSqlQuery query3(*db);
//        bool ok3;
//        ok3 = query3.exec(cmd);
//        if(!ok3)
//            return false;
//        if(ok3)
//        {
//            qDebug() << 3;
//        }
//        if(!query3.next())
//            count3=1;
//        while(query3.next())
//        {
//            te3 += query3.value("te").toDouble();
//            hu3 += query3.value("hu").toDouble();
//            co23 += query3.value("co2").toInt();
//            uv3 += query3.value("uv").toInt();
//            light3 += query3.value("light").toInt();
//            pm253 += query3.value("pm25").toInt();
//            count3++;
//        }
//        QJsonObject obj3;
//        obj3.insert("te", te3/count3);
//        obj3.insert("hu", hu3/count3);
//        obj3.insert("co2", co23/count3);
//        obj3.insert("uv", uv3/count3);
//        obj3.insert("light", light3/count3);
//        obj3.insert("pm25", pm253/count3);
//        arr.append(obj3);

//        if(!query3.next())
//            count3=1;
//        while(query3.next())
//        {
//            te3 += query3.value("te").toDouble();
//            hu3 += query3.value("hu").toDouble();
//            co23 += query3.value("co2").toInt();
//            uv3 += query3.value("uv").toInt();
//            light3 += query3.value("light").toInt();
//            pm253 += query3.value("pm25").toInt();
//            count3++;
//        }
//        QJsonObject obj3;
//        obj3.insert("te", te3/count3);
//        obj3.insert("hu", hu3/count3);
//        obj3.insert("co2", co23/count3);
//        obj3.insert("uv", uv3/count3);
//        obj3.insert("light", light3/count3);
//        obj3.insert("pm25", pm253/count3);
//        arr.append(obj3);

    }
    if(data_type==1)
    {
        int count=0;
        double te=0;
        double hu=0;
        int co2=0;
        int uv=0;
        int light=0;
        int pm25=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`>=DATE_SUB(NOW(), INTERVAL 6 HOUR);")
                .arg(index);
        QSqlQuery query(*db);
        bool ok;
        ok = query.exec(cmd);
        if(!ok)
            return false;
        if(!query.next())
            count=1;
        while(query.next())
        {
            te += query.value("te").toDouble();
            hu += query.value("hu").toDouble();
            co2 += query.value("co2").toInt();
            uv += query.value("uv").toInt();
            light += query.value("light").toInt();
            pm25 += query.value("pm25").toInt();
            count++;
        }
        QJsonObject obj;
        obj.insert("te", te/count);
        obj.insert("hu", hu/count);
        obj.insert("co2", co2/count);
        obj.insert("uv", uv/count);
        obj.insert("light", light/count);
        obj.insert("pm25", pm25/count);
        obj.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addSecs(-6*60*60).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj);

        int count1=0;
        double te1=0;
        double hu1=0;
        int co21=0;
        int uv1=0;
        int light1=0;
        int pm251=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 6 HOUR) AND `time`>=DATE_SUB(NOW(), INTERVAL 12 HOUR);")
                .arg(index);
        QSqlQuery query1(*db);
        bool ok1;
        ok1 = query.exec(cmd);
        if(!ok1)
            return false;
        if(!query1.next())
            count1=1;
        while(query1.next())
        {
            te1 += query1.value("te").toDouble();
            hu1 += query1.value("hu").toDouble();
            co21 += query1.value("co2").toInt();
            uv1 += query1.value("uv").toInt();
            light1 += query1.value("light").toInt();
            pm251 += query1.value("pm25").toInt();
            count1++;
        }
        QJsonObject obj1;
        obj1.insert("te", te1/count);
        obj1.insert("hu", hu1/count);
        obj1.insert("co2", co21/count);
        obj1.insert("uv", uv1/count);
        obj1.insert("light", light1/count);
        obj1.insert("pm25", pm251/count);
        obj1.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addSecs(-6*60*60).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addSecs(-12*60*60).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj1);

        int count2=0;
        double te2=0;
        double hu2=0;
        int co22=0;
        int uv2=0;
        int light2=0;
        int pm252=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 12 HOUR) AND `time`>=DATE_SUB(NOW(), INTERVAL 18 HOUR);")
                .arg(index);
        QSqlQuery query2(*db);
        bool ok2;
        ok2 = query.exec(cmd);
        if(!ok2)
            return false;
        if(!query2.next())
            count2=1;
        while(query2.next())
        {
            te2 += query2.value("te").toDouble();
            hu2 += query2.value("hu").toDouble();
            co22 += query2.value("co2").toInt();
            uv2 += query2.value("uv").toInt();
            light2 += query2.value("light").toInt();
            pm252 += query2.value("pm25").toInt();
            count2++;
        }
        QJsonObject obj2;
        obj2.insert("te", te2/count2);
        obj2.insert("hu", hu2/count2);
        obj2.insert("co2", co22/count2);
        obj2.insert("uv", uv2/count2);
        obj2.insert("light", light2/count2);
        obj2.insert("pm25", pm252/count2);
        obj2.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addSecs(-12*60*60).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addSecs(-18*60*60).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj2);


        int count3=0;
        double te3=0;
        double hu3=0;
        int co23=0;
        int uv3=0;
        int light3=0;
        int pm253=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 18 HOUR) AND `time`>=DATE_SUB(NOW(), INTERVAL 24 HOUR);")
                .arg(index);
        QSqlQuery query3(*db);
        bool ok3;
        ok3 = query3.exec(cmd);
        if(!ok3)
            return false;
        if(!query3.next())
            count3=1;
        while(query3.next())
        {
            te3 += query3.value("te").toDouble();
            hu3 += query3.value("hu").toDouble();
            co23 += query3.value("co2").toInt();
            uv3 += query3.value("uv").toInt();
            light3 += query3.value("light").toInt();
            pm253 += query3.value("pm25").toInt();
            count3++;
        }
        QJsonObject obj3;
        obj3.insert("te", te/count);
        obj3.insert("hu", hu/count);
        obj3.insert("co2", co2/count);
        obj3.insert("uv", uv/count);
        obj3.insert("light", light/count);
        obj3.insert("pm25", pm25/count);
        obj3.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addSecs(-18*60*60).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addSecs(-24*60*60).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj3);

    }
    if(data_type==2)
    {
        int count=0;
        double te=0;
        double hu=0;
        int co2=0;
        int uv=0;
        int light=0;
        int pm25=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`>=DATE_SUB(NOW(), INTERVAL 1 DAY);")
                .arg(index);
        QSqlQuery query(*db);
        bool ok;
        ok = query.exec(cmd);
        qDebug() << ok;
        if(!ok)
            return false;
        if(!query.next())
            count=1;
        while(query.next())
        {
            te += query.value("te").toDouble();
            hu += query.value("hu").toDouble();
            co2 += query.value("co2").toInt();
            uv += query.value("uv").toInt();
            light += query.value("light").toInt();
            pm25 += query.value("pm25").toInt();
            count++;
        }
        qDebug() << te;
        QJsonObject obj;
        obj.insert("te", te/count);
        obj.insert("hu", hu/count);
        obj.insert("co2", co2/count);
        obj.insert("uv", uv/count);
        obj.insert("light", light/count);
        obj.insert("pm25", pm25/count);
        obj.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addDays(-1).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj);
        qDebug() <<1;

//        obj.insert("index", query.value("device_id").toInt());
//        obj.insert("te", query.value("te").toDouble());
//        obj.insert("hu", query.value("hu").toDouble());
//        obj.insert("co2", query.value("co2").toInt());
//        obj.insert("uv", query.value("uv").toInt());
//        obj.insert("light", query.value("light").toInt());
//        obj.insert("mq5", query.value("mq5").toInt());
//        obj.insert("fire", query.value("fire").toInt());
//        obj.insert("mq2", query.value("mq2").toInt());
//        obj.insert("inf", query.value("inf").toInt());
//        obj.insert("pm25", query.value("pm25").toInt());
//        obj.insert("DS", query.value("DS").toInt());
//        obj.insert("FS", query.value("FS").toInt());
//        obj.insert("time", query.value("time").toString());


        int count1=0;
        double te1=0;
        double hu1=0;
        int co21=0;
        int uv1=0;
        int light1=0;
        int pm251=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 1 DAY) AND `time`>=DATE_SUB(NOW(), INTERVAL 2 DAY);")
                .arg(index);
        QSqlQuery query1(*db);
        bool ok1;
        ok1 = query1.exec(cmd);
        if(!ok1)
            return false;
        if(!query1.next())
            count1=1;
        while(query1.next())
        {
            te1 += query1.value("te").toDouble();
            hu1 += query1.value("hu").toDouble();
            co21 += query1.value("co2").toInt();
            uv1 += query1.value("uv").toInt();
            light1 += query1.value("light").toInt();
            pm251 += query1.value("pm25").toInt();
            count1++;
        }
        qDebug() << te1;
        QJsonObject obj1;
        obj1.insert("te", te1/count1);
        obj1.insert("hu", hu1/count1);
        obj1.insert("co2", co21/count1);
        obj1.insert("uv", uv1/count1);
        obj1.insert("light", light1/count1);
        obj1.insert("pm25", pm251/count1);
        obj1.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addDays(-1).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addDays(-2).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj1);
        qDebug() << 2;
        int count2=0;
        double te2=0;
        double hu2=0;
        int co22=0;
        int uv2=0;
        int light2=0;
        int pm252=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 2 DAY) AND `time`>=DATE_SUB(NOW(), INTERVAL 3 DAY);")
                .arg(index);
        QSqlQuery query2(*db);
        bool ok2;
        ok2 = query.exec(cmd);
        if(!ok2)
            return false;
        if(!query2.next())
            count2=1;
        while(query2.next())
        {
            te2 += query2.value("te").toDouble();
            hu2 += query2.value("hu").toDouble();
            co22 += query2.value("co2").toInt();
            uv2 += query2.value("uv").toInt();
            light2 += query2.value("light").toInt();
            pm252 += query2.value("pm25").toInt();
            count2++;
        }
        qDebug() << te2;
        QJsonObject obj2;
        obj2.insert("te", te2/count2);
        obj2.insert("hu", hu2/count2);
        obj2.insert("co2", co22/count2);
        obj2.insert("uv", uv2/count2);
        obj2.insert("light", light2/count2);
        obj2.insert("pm25", pm252/count2);
        obj2.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addDays(-2).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addDays(-3).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj2);
        qDebug() << 3;

        int count3=0;
        double te3=0;
        double hu3=0;
        int co23=0;
        int uv3=0;
        int light3=0;
        int pm253=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 3 DAY) AND `time`>=DATE_SUB(NOW(), INTERVAL 4 DAY);")
                .arg(index);
        QSqlQuery query3(*db);
        bool ok3;
        ok3 = query3.exec(cmd);
        if(!ok3)
            return false;
        if(!query3.next())
            count3=1;
        while(query3.next())
        {
            te3 += query3.value("te").toDouble();
            hu3 += query3.value("hu").toDouble();
            co23 += query3.value("co2").toInt();
            uv3 += query3.value("uv").toInt();
            light3 += query3.value("light").toInt();
            pm253 += query3.value("pm25").toInt();
            count3++;
        }
        qDebug() << te3;
        QJsonObject obj3;
        obj3.insert("te", te3/count3);
        obj3.insert("hu", hu3/count3);
        obj3.insert("co2", co23/count3);
        obj3.insert("uv", uv3/count);
        obj3.insert("light", light3/count3);
        obj3.insert("pm25", pm253/count3);
        obj3.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addDays(-3).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addDays(-4).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj3);
        qDebug() << 4;
        int count4=0;
        double te4=0;
        double hu4=0;
        int co24=0;
        int uv4=0;
        int light4=0;
        int pm254=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 4 DAY) AND `time`>=DATE_SUB(NOW(), INTERVAL 5 DAY);")
                .arg(index);
        QSqlQuery query4(*db);
        bool ok4;
        ok4 = query4.exec(cmd);
        if(!ok4)
            return false;
        if(!query4.next())
            count4=1;
        while(query4.next())
        {
            te4 += query4.value("te").toDouble();
            hu4 += query4.value("hu").toDouble();
            co24 += query4.value("co2").toInt();
            uv4 += query4.value("uv").toInt();
            light4 += query4.value("light").toInt();
            pm254 += query4.value("pm25").toInt();
            count4++;
        }
        qDebug() << te4;
        QJsonObject obj4;
        obj4.insert("te", te4/count4);
        obj4.insert("hu", hu4/count4);
        obj4.insert("co2", co24/count4);
        obj4.insert("uv", uv4/count4);
        obj4.insert("light", light4/count4);
        obj4.insert("pm25", pm254/count4);
        obj4.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addDays(-4).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addDays(-5).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj4);
        qDebug() <<  5;

        int count5=0;
        double te5=0;
        double hu5=0;
        int co25=0;
        int uv5=0;
        int light5=0;
        int pm255=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 5 DAY) AND `time`>=DATE_SUB(NOW(), INTERVAL 6 DAY);")
                .arg(index);
        QSqlQuery query5(*db);
        bool ok5;
        ok5 = query5.exec(cmd);
        if(!ok5)
            return false;
        if(!query5.next())
            count5=1;
        while(query5.next())
        {
            te5 += query5.value("te").toDouble();
            hu5 += query5.value("hu").toDouble();
            co25 += query5.value("co2").toInt();
            uv5 += query5.value("uv").toInt();
            light5 += query5.value("light").toInt();
            pm255 += query5.value("pm25").toInt();
            count5++;
        }
        qDebug() << te5;
        QJsonObject obj5;
        obj5.insert("te", te5/count5);
        obj5.insert("hu", hu5/count5);
        obj5.insert("co2", co25/count5);
        obj5.insert("uv", uv5/count5);
        obj5.insert("light", light5/count5);
        obj5.insert("pm25", pm255/count5);
        obj5.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addDays(-5).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addDays(-6).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj5);
        qDebug() << 6;

        int count6=0;
        double te6=0;
        double hu6=0;
        int co26=0;
        int uv6=0;
        int light6=0;
        int pm256=0;
        cmd = QString("SELECT * FROM `sh_value` "
                      "WHERE `device_id`='%1' AND `time`<=DATE_SUB(NOW(), INTERVAL 6 DAY) AND `time`>=DATE_SUB(NOW(), INTERVAL 7 DAY);")
                .arg(index);
        QSqlQuery query6(*db);
        bool ok6;
        ok6 = query6.exec(cmd);
        if(!ok6)
            return false;
        if(!query6.next())
            count6=1;
        while(query6.next())
        {
            te6 += query6.value("te").toDouble();
            hu6 += query6.value("hu").toDouble();
            co26 += query6.value("co2").toInt();
            uv6 += query6.value("uv").toInt();
            light6 += query6.value("light").toInt();
            pm256 += query6.value("pm25").toInt();
            count6++;
        }
        qDebug() << te6;
        QJsonObject obj6;
        obj6.insert("te", te6/count6);
        obj6.insert("hu", hu6/count6);
        obj6.insert("co2", co26/count6);
        obj6.insert("uv", uv6/count6);
        obj6.insert("light", light6/count6);
        obj6.insert("pm25", pm256/count6);
        obj6.insert("time", QString("%1-%2").arg(QDateTime::currentDateTime().addDays(-6).toString("yyyy-MM-dd hh:mm:ss"))
                   .arg(QDateTime::currentDateTime().addDays(-7).toString("yyyy-MM-dd hh:mm:ss")));
        arr.append(obj6);
        qDebug() << 7;
    }
//    if(data_type==3)
//    {
//        cmd = QString("SELECT * FROM `sh_value` "
//                      "WHERE `device_id`='%1' AND `time`>=DATE_SUB(NOW(), INTERVAL 1 MONTH);")
//                .arg(index);
//        QSqlQuery query(*db);
//        bool ok;
//        ok = query.exec(cmd);
//        if(!ok)
//            return false;
//        while(query.next())
//        {
//            QJsonObject obj;
//            obj.insert("index", query.value("device_id").toInt());
//            obj.insert("te", query.value("te").toDouble());
//            obj.insert("hu", query.value("hu").toDouble());
//            obj.insert("co2", query.value("co2").toInt());
//            obj.insert("uv", query.value("uv").toInt());
//            obj.insert("light", query.value("light").toInt());
//            obj.insert("mq5", query.value("mq5").toInt());
//            obj.insert("fire", query.value("fire").toInt());
//            obj.insert("mq2", query.value("mq2").toInt());
//            obj.insert("inf", query.value("inf").toInt());
//            obj.insert("pm25", query.value("pm25").toInt());
//            obj.insert("DS", query.value("DS").toInt());
//            obj.insert("FS", query.value("FS").toInt());
//            obj.insert("time", query.value("time").toString());
//            arr.append(obj);
//        }

//    }
//    if(data_type==4)
//    {
//        cmd = QString("SELECT * FROM `sh_value` "
//                      "WHERE `device_id`='%1' AND `time`>=DATE_SUB(NOW(), INTERVAL 1 YEAR);")
//                .arg(index);
//        QSqlQuery query(*db);
//        bool ok;
//        ok = query.exec(cmd);
//        if(!ok)
//            return false;
//        while(query.next())
//        {
//            QJsonObject obj;
//            obj.insert("index", query.value("device_id").toInt());
//            obj.insert("te", query.value("te").toDouble());
//            obj.insert("hu", query.value("hu").toDouble());
//            obj.insert("co2", query.value("co2").toInt());
//            obj.insert("uv", query.value("uv").toInt());
//            obj.insert("light", query.value("light").toInt());
//            obj.insert("mq5", query.value("mq5").toInt());
//            obj.insert("fire", query.value("fire").toInt());
//            obj.insert("mq2", query.value("mq2").toInt());
//            obj.insert("inf", query.value("inf").toInt());
//            obj.insert("pm25", query.value("pm25").toInt());
//            obj.insert("DS", query.value("DS").toInt());
//            obj.insert("FS", query.value("FS").toInt());
//            obj.insert("time", query.value("time").toString());
//            arr.append(obj);
//        }

//    }
    return true;
}


