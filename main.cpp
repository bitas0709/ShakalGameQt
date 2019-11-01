#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    //w.setWindowTitle("ShakalGame");
    w.setWindowTitle("Escape from UMNIK");
    w.setFixedSize(500, 500);
    w.show();

    return a.exec();
}
