#include "sqlthreaddispatch.h"
#include <QSemaphore>
#include <QThread>
#include "sqlexec.h"
#include "configexec.h"
#define DISPATCHSIZE 1
SqlThreadDispatch *SqlThreadDispatch::obj = nullptr;

SqlThreadDispatch::SqlThreadDispatch(QObject *parent)
    : QObject{parent}
    , semaphore(new QSemaphore(DISPATCHSIZE))
{
    initDispatch();
}

SqlThreadDispatch *SqlThreadDispatch::getObject()
{
    if(obj == nullptr)
        obj = new SqlThreadDispatch;
    return obj;
}

SqlExec *SqlThreadDispatch::getExec()
{
    semaphore->acquire();
    SqlExec *exec = nullptr;
    for(int i = 0; i < sqlDispatchList.length();
        i++)
    {
        if(!sqlDispatchList.at(i)->getState()){
            exec = sqlDispatchList.at(i);
            break;
        }
    }
    if(exec != nullptr)
        exec->setState(true);
    return exec;
}

void SqlThreadDispatch::freeExec(SqlExec *exec)
{
    if(exec == nullptr)
        return;
    exec->setState(false);
    semaphore->release();
}

QString SqlThreadDispatch::getStateText()
{
    //总体状态概况 + 具体的情况1成功/0失败
    int suc=0, err=0;
    QString msg;
    for(int i = 0; i < sqlDispatchList.length(); i++)
    {
        bool ok = sqlDispatchList.at(i)
                ->getConnectState();
        if(ok){
            suc++;
            msg.append("1");
        }
        else{
            err++;
            msg.append("0");
        }
    }
    return QString("总连接：%1，成功：%2，失败：%3；提示：%4")
            .arg(DISPATCHSIZE).arg(suc).arg(err).arg(msg);
}

void SqlThreadDispatch::initDispatch()
{
    QString ip, username, password, dbName;
    int port;
    ConfigExec::getObject()->getSqlConfig(
        ip, port, username, password, dbName);
    for(int i = 0; i < DISPATCHSIZE; i++)
    {
        SqlExec *exec = new SqlExec
            (ip, port, username, password,
             dbName,
             QString("Connect_%1").arg(i));
        QThread *th = new QThread;
        th->start();
        exec->moveToThread(th);
        sqlDispatchList.append(exec);
    }
}









