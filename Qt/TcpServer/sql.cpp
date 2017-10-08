#include "sql.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#define SqlPort 9999

Sql::Sql(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "student");
    db.setDatabaseName("./user.db");
    db.setUserName("zhangjian");
    db.setPassword("zhangjian123");
    db.setHostName("localhost");
    db.setPort(SqlPort);
    //    db.setConnectOptions( 1 );

    if (!db.open())
    {
        qDebug() << "Error: Failed to connect database." << db.lastError();
    }

    QSqlQuery query(db);

    QString create_sql = "create table student ( name varchar(30), password varchar(30) )";
    query.prepare(create_sql);

    if( query.exec() )
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
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    qDebug()<<"called";
    qDebug()<<query.value( name );
}

bool Sql::insert(QString name, QString password)
{
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare("insert into student values(?, ?, ?, ?)");

    query.bindValue(0, name.toStdString().c_str());
    query.bindValue(1, password.toStdString().c_str());

    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return false;
    }
    return true;
}
