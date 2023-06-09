#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

namespace Ui {
class MainPage;
}
class QTimer;
class QTcpSocket;
class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

private slots:
    void receiveTimerTimeoutSlot();
    void uvTimerTimeoutSlot();
    void te1TimerTimeoutSlot();
    void hu1TimerTimeoutSlot();
    void lightTimerTimeoutSlot();
    void mq5TimerTimeoutSlot();
    void fireTimerTimeoutSlot();
    void mq2TimerTimeoutSlot();
    void infTimerTimeoutSlot();
    void pm25TimerTimeoutSlot();
    void te2TimerTimeoutSlot();
    void hu2TimerTimeoutSlot();
    void DSTimerTimeoutSlot();
    void FSTimerTimeoutSlot();
    void startTimerTimeoutSlot();

    void deviceLoginSlot(QString index,bool re,int error_id,QString identification,QString time);
    void openLightSlot(QString index,int id,int brightness);
    void openRGBLightSlot(QString index, int r, int g, int b);
    void openDevice1To8Slot(QString index, int id, bool sw);

    void on_btnOpenSerial_clicked();

    //void on_btnSend_clicked();

    void on_hsLight3_sliderReleased();

    void on_hsLight1_sliderReleased();

    void on_hsLight2_sliderReleased();

    void on_hsLight4_sliderReleased();

    void on_btnAlarmOpen_clicked();

    void on_btnAlarmClose_clicked();

    void on_btnAlarmLedOpen_clicked();

    void on_btnAlarmLedClose_clicked();

    void on_btnSteerengineOpen_clicked();

    void on_btnSteerengineClose_clicked();

    void on_btnStepmotorOpen_clicked();

    void on_btnStepmotorClose_clicked();

    void on_btnFanOpen_clicked();

    void on_btnFanClose_clicked();

    void on_btnRelay1Open_clicked();

    void on_btnRelay1Close_clicked();

    void on_btnRelay2Open_clicked();

    void on_btnRelay2Close_clicked();

    void on_btnLockOpen_clicked();

    void on_btnLockClose_clicked();

    void on_btnColor_clicked();

    void on_btnGetCo2_clicked();

    void on_btnGetUv_clicked();

    void on_btnGetTe1_clicked();

    void on_btnGethu1_clicked();

    void on_btnGetLight_clicked();

    void on_btnGetmq5_clicked();

    void on_btnGetFire_clicked();

    void on_btnGetMq2_clicked();

    void on_btnGetInf_clicked();

    void on_btnGetPm25_clicked();

    void on_btnGetTe2_clicked();

    void on_btnGetHu2_clicked();

    void on_btnGetData_clicked();

    void on_btnUploadData_clicked();

    void on_btnDS_clicked();

    void on_btnFS_clicked();

    void on_btnClearData_clicked();

private:
    Ui::MainPage *ui;
    QTimer *receiveTimer;
    QTimer *uvTimer;
    QTimer *te1Timer;
    QTimer *hu1Timer;
    QTimer *lightTimer;
    QTimer *mq5Timer;
    QTimer *fireTimer;
    QTimer *mq2Timer;
    QTimer *infTimer;
    QTimer *pm25Timer;
    QTimer *te2Timer;
    QTimer *hu2Timer;
    QTimer *DSTimer;
    QTimer *FSTimer;
    QTimer *start;
    QTcpSocket *client;
    QString Index;
    QString Identification;
    bool Re;
};

#endif // MAINPAGE_H
