#ifndef CONFIGEXEC_H
#define CONFIGEXEC_H

#include <QObject>

class ConfigExec : public QObject
{
    Q_OBJECT
protected:
    explicit ConfigExec(QObject *parent = nullptr);

public:
    static ConfigExec *getObject();
    /**
     * @brief 获取数据库配置
     * @param ip
     * @param port
     * @param username
     * @param password
     * @param dbName
     * @return 获取的状态
     */
    bool getSqlConfig(QString &ip,
                      int &port,
                      QString &username,
                      QString &password,
                      QString &dbName);
    /**
     * @brief 获取网络配置
     * @param port
     * @return
     */
    bool getNetConfig(int &port);

protected:
    static ConfigExec *obj;

};

#endif // CONFIGEXEC_H
