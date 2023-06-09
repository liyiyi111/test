#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QByteArray>
#include <QStandardItem>
#include <QTimer>
namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();


private slots:
    void userTimerTimeoutSlot();
    void userLoginSlot(bool re);
    void userRequestRealSlot(int index, double te, double hu, int co2, int uv, int light,
                           int mq5, int fire, int mq2, int inf, int pm25, int DS, int FS ,QString time);
    void userRequestPastSlot(const QByteArray &arr);

    void on_btnUserLogin_clicked();

    void on_hsLight1_sliderReleased();

    void on_btnRequestReal_clicked();

    void on_btnRequestPast_clicked();

    void on_hsLight2_sliderReleased();

    void on_hsLight3_sliderReleased();

    void on_hsLight4_sliderReleased();

    void on_btnColorLight_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

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

private:
    Ui::MainPage *ui;
    QStandardItemModel *model;
    QStandardItemModel *model1;
    QStandardItemModel *model2;
    QStandardItemModel *model3;
    QTimer* t1;
};

#endif // MAINPAGE_H
