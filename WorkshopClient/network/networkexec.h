#ifndef NETWORKEXEC_H
#define NETWORKEXEC_H

#include <QObject>
#include <QDateTime>
#include <QByteArray>
class QTcpSocket;
class QTimer;
class NetworkExec : public QObject
{
    Q_OBJECT
protected:
    explicit NetworkExec(QObject *parent = nullptr);

public:
    static NetworkExec *getObject();
    void userLogin(QString username, QString password);
    void userRequestReal(QString index);
    void userRequestPast(QString index, int dataType);
    void userLightControl(QString index, int id, int brightness);
    void userColorLightControl(QString index, int r, int g, int b);
    void userDeviceControl(QString index, int id, bool sw);

signals:
    void userLoginRe(bool re);
    void userRequestRealRe(int index, double te, double hu, int co2, int uv, int light,
                           int mq5, int fire, int mq2, int inf, int pm25, int DS, int FS, QString time);
    void userRequestPastRe(const QByteArray &arr);

    void netDisconnected();
    void netConnected();

protected slots:
    void clientReadyReadSlot();
    void stateTimerTimeoutSlot();

protected:
    void connectToHost();
    void handleFrame(const QByteArray &arr);

    static NetworkExec *obj;
    QTcpSocket *client;
    QTimer *stateTimer;
    QString checkKey;
    QDateTime lastHeartTime;
    QList<QString> list;
};

#endif // NETWORKEXEC_H
