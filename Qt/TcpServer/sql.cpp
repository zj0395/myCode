#include "sql.h"
#include <QDebug>
#include <QSqlError>

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

    if (!db.open())
    {
        qDebug() << "Error: Failed to connect database." << db.lastError();
    }

    query = new QSqlQuery(db);

    QString create_sql = "create table student (id int primary key, name varchar(30), password varchar(30))";
    query->prepare(create_sql);

    if( query->exec() )
    {
        qDebug() << QObject::tr("数据库表创建成功！\n");
    }
    else
    {
        qDebug() << QObject::tr("数据库表创建失败！\n");
    }
}

Sql::~Sql()
{
    db.close();
}

bool Sql::login(QString name, QString password)
{
}
