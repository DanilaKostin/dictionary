#include "mainwindow.h"
#include "qmap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMap <QString, QString> dict;
    MainWindow w;
    w.show();
    return a.exec();
}
