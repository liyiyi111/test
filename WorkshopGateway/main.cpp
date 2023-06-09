#include "mainpage.h"
#include <QApplication>
#include "zigbeedriver.h"
#include "zigbeeprotocol.h"
#include "networkexec.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ZigbeeDriver::getObject();
    ZigbeeProtocol::getObject();
    NetworkExec::getObject();
    MainPage w;
    w.show();

    return a.exec();
}
