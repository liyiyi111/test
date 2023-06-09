#ifndef ZIGBEEPROTOCOL_H
#define ZIGBEEPROTOCOL_H

#include <QObject>
class QTimer;
/**
 * @brief The Zigbee协议类
 */
class ZigbeeProtocol : public QObject
{
    Q_OBJECT
protected:
    explicit ZigbeeProtocol(QObject *parent = nullptr);
public:
    static ZigbeeProtocol *getObject();
    bool openLight1(int light);
    bool openLight2(int light);
    /**
     * @brief 控制LED灯 3
     * @param light 亮度0-255
     * @return
     */
    bool openLight3(int light);
    bool openLight4(int light);
    /**
     * @brief 控制炫彩LED灯
     * @param r
     * @param g
     * @param b
     * @return
     */
    bool openRGBLight(int r, int g, int b);
    bool openRGBLight(QColor color);
    /**
     * @brief 报警器的控制
     * @param status
     * @return
     */
    bool alarmControl(int status);
    /**
     * @brief 报警灯的控制
     * @param status
     * @return
     */
    bool alarmLedControl(int status);
    /**
     * @brief 舵机的控制
     * @param status
     * @return
     */
    bool steerengineControl(int status);
    /**
     * @brief 步进电机的控制
     * @param status
     * @return
     */
    bool stepmotorControl(int status);
    /**
     * @brief 风扇的控制
     * @param status
     * @return
     */
    bool fanControl(int status);
    /**
     * @brief 继电器1的控制
     * @param status
     * @return
     */
    bool relay1Control(int status);
    /**
     * @brief 继电器2的控制
     * @param status
     * @return
     */
    bool relay2Control(int status);
    /**
     * @brief 电磁锁的控制
     * @param status
     * @return
     */
    bool lockControl(int status);

    void requestCo2();
    int getCo2();
    void requestUv();
    int getUv();
    void requestTe();
    double getTe();
    void requestHu();
    double getHu();
    void requestLight();
    int getLight();
    void requestMq5();
    bool getMq5();
    void requestFire();
    bool getFire();
    void requestMq2();
    bool getMq2();
    void requestInf();
    bool getInf();
    void requestPm25();
    int getPm25();
    void requestTe2();
    double getTe2();
    void requestHu2();
    double getHu2();
    void requestDS();
    bool getDS();
    void requestFS();
    bool getFS();
signals:

protected slots:
    void sendTimerTimeoutSlot();
    void requestTimerTimeoutSlot();
    void receiveFromSerialPortSlot(const QByteArray &data);
protected:
    void addControlCmd(QByteArray cmd);
    void addSensorRequestCmd(QByteArray cmd);
    void handleFrame(const QByteArray &data);
    static ZigbeeProtocol *obj;
    QList<QByteArray > dataList;
    QTimer *sendTimer;

    QTimer *requestTimer;

    QByteArray dataAll;
    int co2;
    int uv; //紫外线
    double te,hu;
    int light;  //光照
    bool mq5;   //甲烷
    bool fire;
    bool mq2;   //烟雾
    bool inf;   //人体红外
    int pm2_5;
    double te2,hu2;
    bool DS;
    bool FS;
};

#endif // ZIGBEEPROTOCOL_H
