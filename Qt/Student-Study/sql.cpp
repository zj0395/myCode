#include "sql.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#define SqlPort 9999

Sql::Sql(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "DB_student");
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
        qDebug() << QObject::tr("数据库表创建成功！\n");
    else
        qDebug() << QObject::tr("数据库表创建失败！\n");

    create_sql = "create table idiom ( str varchar(30), info varchar(200) )";
    query.prepare(create_sql);

    if( query.exec() )
        qDebug() << QObject::tr("数据库表创建成功！\n");
    else
        qDebug() << QObject::tr("数据库表创建失败！\n");
}

Sql *Sql::getSql()
{
    static Sql w;
    return &w;
}

Sql::~Sql()
{
    db.close();
}

MessageType Sql::login(const QString name, const QString password, QString tableName)
{
    QSqlDatabase db = QSqlDatabase::database("DB_student");//建立数据库连接
    QSqlQuery query(db);
    query.exec(  QString("select * from %1").arg(tableName) );

    //遍历所有项，来检查用户名和密码
    //效率低，应该有更高效的方法
    while (query.next())
    {
        if( name == query.value(0).toString() )
        {
            if( password == query.value(1).toString() )
                return M_LoginSuccess;
            else
                return M_WrongPassword;
        }
    }

    return M_WrongUserName;
}

MessageType Sql::insert(QString name, QString password)
{
    //检查要插入的用户名是否已存在
    if(  find(name, "student")  )
        return M_UserNameExist;

    QSqlDatabase db = QSqlDatabase::database("DB_student");//建立数据库连接
    QSqlQuery query(db);
    query.prepare("insert into student values(?, ?)");
    query.bindValue(0, name.toStdString().c_str());
    query.bindValue(1, password.toStdString().c_str());

    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return M_SqlInsertWrong;
    }
    return M_RegisterSuccess;
}

MessageType Sql::setInformation(QString name, QString result)
{
    //检查要插入的用户名是否已存在
    if(  find(name, "idiom")  )
        return M_UserNameExist;

    QSqlDatabase db = QSqlDatabase::database("DB_student");//建立数据库连接
    QSqlQuery query(db);

    query.prepare("insert into idiom values(?, ?)");
    query.bindValue(0, name.toStdString().c_str());
    query.bindValue(1, result.toStdString().c_str());

    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
        return M_SqlInsertWrong;
    }
    return M_RegisterSuccess;
}

MessageType Sql::getInformation(QString name, QString &result)
{
    QSqlDatabase db = QSqlDatabase::database("DB_student");//建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from idiom");

    //遍历所有项，来检查用户名和密码
    //效率低，应该有更高效的方法
    while (query.next())
    {
        if( name == query.value(0).toString() )
        {
            result = query.value(1).toString();
            return M_LoginSuccess;
        }
    }
    return M_WrongUserName;
}

bool Sql::find(QString name, QString tableName)
{
    //检查要插入的用户名是否已存在
    //虽然效率低，但简单方便
    if( login(name, "", tableName) == M_WrongUserName )
        return false;//不存在
    return true;//已存在
}
