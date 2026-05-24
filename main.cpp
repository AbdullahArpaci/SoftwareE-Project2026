#include "dekontservisi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DekontServisi w;
    w.show();
    return a.exec();
}
