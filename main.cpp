#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("ShakalGame");
    w.setFixedSize(700, 700);
    w.show();

    return a.exec();
}
