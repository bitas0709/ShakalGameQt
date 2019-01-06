#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w->setWindowIcon(QIcon(":/resources/images/logo.png"));
    w->setWindowTitle("ShakalGame");
    w->setFixedSize(800, 600);
    w->show();

    return a.exec();
}
