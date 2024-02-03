#include "graf.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    graf w;
    w.show();
    return a.exec();
}

