#include <QCoreApplication>
#include "networkexec.h"
#include "sqlthreaddispatch.h"
#include "logexec.h"



#include "sqlexec.h"
#include <QJsonArray>
#include <QDebug>

int main(int argc, char *argv[])
{
   // QCoreApplication a(argc, argv);
    QCoreApplication a(argc, argv);
    LogExec::getObject()->OutPutMsg("数据库模块启动");
    SqlThreadDispatch::getObject();
    LogExec::getObject()->OutPutMsg(
        SqlThreadDispatch::getObject()->getStateText()
                );
    LogExec::getObject()->OutPutMsg("网络模块启动");
    NetworkExec::getObject();
    NetworkExec::getObject()->startServer();
    LogExec::getObject()->OutPutMsg("网络模块启动完成");
//    SqlThreadDispatch::getObject();
//    NetworkExec::getObject()
//        ->startServer();
    return a.exec();
}
