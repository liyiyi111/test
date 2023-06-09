#include "logexec.h"
#include <QDateTime>
#include <QDebug>
LogExec *LogExec::obj = nullptr;
LogExec::LogExec(QObject *parent)
    : QObject{parent}
{

}

LogExec *LogExec::getObject()
{
    if(obj == nullptr)
        obj = new LogExec;
    return obj;
}

void LogExec::OutPutMsg(QString msg)
{
    qDebug() << QString("[%1]:%2")
                .arg(QDateTime::currentDateTime()
                     .toString("yyyy-MM-dd hh:mm:ss.zzz"))
                .arg(msg);
}

void LogExec::OutPutWarningMsg(QString msg)
{
    qDebug() << QString("[%1](Warning):%2")
                .arg(QDateTime::currentDateTime()
                     .toString("yyyy-MM-dd hh:mm:ss.zzz"))
                .arg(msg);
}

void LogExec::OutPutErrorMsg(QString msg)
{
    qDebug() << QString("[%1](Error):%2")
                .arg(QDateTime::currentDateTime()
                     .toString("yyyy-MM-dd hh:mm:ss.zzz"))
                .arg(msg);
}








