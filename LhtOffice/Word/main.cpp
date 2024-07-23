#include "mainwindow.h"
#include <QApplication>
#include "qworddemo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWordDemo w;
    w.show();

    return a.exec();
}
