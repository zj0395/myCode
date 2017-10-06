#include "sql.h"
#define SqlPort 9999

Sql::Sql(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Chat");
    db.setUserName("zhangjian");
    db.setPassword("zhangjian123");
    db.setHostName("localhost");
    db.setPort(SqlPort);
    //    db.setConnectOptions( 1 );
}

bool Sql::login(QString name, QString password)
{
}
