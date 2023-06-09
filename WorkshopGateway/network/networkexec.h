#ifndef NETWORKEXEC_H
#define NETWORKEXEC_H

#include <QObject>
#include <QString>
#include <QByteArray>
class QTcpSocket;
class NetworkExec : public QObject
{
    Q_OBJECT
protected:
    explicit NetworkExec(QObject *parent = nullptr);
public:
    static NetworkExec *getObject();
    void deviceLogin(QString index, QString password);

signals:
    void deviceLoginRe(QString index,bool re,int error_id,QString identification,QString time);
    void openLightSig(QString index,int id, int brightness);
    void openRGBLightSig(QString index, int r, int g, int b);
    void openDevice1To8Re(QString index, int id, bool sw);

public slots:
protected slots:
    void clientReadyReadSlot();
protected:
    void handleFrame(const QByteArray &arr);
    static NetworkExec *obj;
    QTcpSocket *client;
};

#endif // NETWORKEXEC_H
