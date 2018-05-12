#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    system("xset -dpms");
    system("xset s off");
    QApplication a(argc, argv);
    MainWindow w;

    w.setDesktop( a.desktop() );
    w.show();

    return a.exec();
}
