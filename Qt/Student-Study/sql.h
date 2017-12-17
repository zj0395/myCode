#ifndef SQL_H
#define SQL_H

#include "../TcpDefines.h"
#include <QObject>
#include <QSqlDatabase>

class Sql : public QObject
{
    Q_OBJECT
public:

    static Sql* getSql();

    ~Sql();
    MessageType login(const QString name, const QString password, QString tableName = "student");
    MessageType insert(QString name, QString password);
    MessageType setInformation( QString name, QString   result );
    MessageType getInformation( QString name, QString & result );
    bool find(QString name , QString tableName);

signals:

public slots:

private:
    explicit Sql(QObject *parent = nullptr);

    QSqlDatabase db;
};

#endif // SQL_H
