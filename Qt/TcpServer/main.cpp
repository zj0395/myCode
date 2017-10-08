#include "widget.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer s;

    return a.exec();
}
