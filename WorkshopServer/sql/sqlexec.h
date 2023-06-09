#ifndef SQLEXEC_H
#define SQLEXEC_H

#include <QObject>
#include <QJsonArray>
class QSqlDatabase;
/**
 * @brief 配置类
 */
class SqlExec : public QObject
{
    Q_OBJECT
public:
    explicit SqlExec(
            QString ip, int port,
            QString username, QString password,
            QString dbName, QString connectName,
            QObject *parent = nullptr);
    /**
     * @brief 获取数据库状态函数
     * @return
     */
    bool getConnectState();

    /**
     * @brief 设置当前繁忙情况
     * @param s
     */
    void setState(bool s);
    /**
     * @brief 获取当前的繁忙情况
     * @return
     */
    bool getState();
    /**
     * @brief 设备登录
     * @param deviceId
     * @param deviceKey
     * @return
     */
    bool deviceLogin(QString deviceId, QString deviceKey);
    /**
     * @brief 保存数据
     * @param deviceId
     * @param te
     * @param hu
     * @param co2
     * @param mq2
     * @return
     */

    bool deviceSaveData(QString deviceId, double te, double hu, int co2, int uv, int light, int pm25, int mq5, int fire, int mq2, int inf, int DS, int FS);
    bool userLogin(QString username, QString password);
    bool getCurSenorData(QString index, QJsonArray &arr);
    bool getPastSenorData(QString index, int data_type, QJsonArray &arr);

protected:
    bool state = false; //是否繁忙
    QSqlDatabase *db;
};

#endif // SQLEXEC_H
