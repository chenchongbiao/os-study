#include <QtWidgets/QApplication>

#include "qdbusserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDBusServer w;
    w.show();

    return a.exec();
}
