#include "mw1.h"
#include <QApplication>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MW1 mw;
    mw.show();

    return a.exec();
}
