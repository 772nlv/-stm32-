#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow M;
    toStm32Window w;
    w.show();
    return a.exec();
}
