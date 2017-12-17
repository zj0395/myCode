#include <QApplication>
#include "sql.h"
#include <QDebug>
#include "loginform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();

    return a.exec();
}
