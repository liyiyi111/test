#include "configexec.h"
#include <QSettings>
#define CONFIGFILENAME  "config.ini"
#define SQLGROUPNAME    "database"
#define SQLIP           "ip"
#define SQLPORT         "port"
#define SQLUSERNAME     "username"
#define SQLPASSWORD     "password"
#define SQLDBNAME       "db_name"

#define NETGROUPNAME    "network"
#define NETPORT         "listen_port"

ConfigExec *ConfigExec::obj = nullptr;
ConfigExec::ConfigExec(QObject *parent)
    : QObject{parent}
{

}

ConfigExec *ConfigExec::getObject()
{
    if(obj == nullptr)
        obj = new ConfigExec;
    return obj;
}

bool ConfigExec::getSqlConfig(QString &ip, int &port, QString &username, QString &password, QString &dbName)
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(SQLGROUPNAME);

    QStringList keys = set.allKeys();
    if(!keys.contains(SQLIP))
        set.setValue(SQLIP, "127.0.0.1");
    ip = set.value(SQLIP).toString();
    if(!keys.contains(SQLPORT))
        set.setValue(SQLPORT, 3306);
    port = set.value(SQLPORT).toInt();
    if(!keys.contains(SQLUSERNAME))
        set.setValue(SQLUSERNAME, "root");
    username = set.value(SQLUSERNAME).toString();
    if(!keys.contains(SQLPASSWORD))
        set.setValue(SQLPASSWORD, "");
    password = set.value(SQLPASSWORD).toString();
    if(!keys.contains(SQLDBNAME))
        set.setValue(SQLDBNAME, "smart");
    dbName = set.value(SQLDBNAME).toString();



    set.endGroup();
    return true;
}

bool ConfigExec::getNetConfig(int &port)
{
    QSettings set(CONFIGFILENAME,
                  QSettings::IniFormat);
    set.beginGroup(NETGROUPNAME);

    QStringList keys = set.allKeys();
    if(!keys.contains(NETPORT))
        set.setValue(NETPORT, 20001);
    port = set.value(NETPORT).toInt();

    set.endGroup();
    return true;
}






