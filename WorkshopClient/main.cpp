#include "mainpage.h"
#include <QApplication>
#include "networkexec.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkExec::getObject();
    MainPage w;
    w.show();

    return a.exec();
}
