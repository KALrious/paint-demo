#include "mylittlepaint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyLittlePaint w;
    w.show();
    return a.exec();
}
