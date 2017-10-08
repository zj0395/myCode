#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);
    ~Sql();
    bool login(QString name, QString password);

signals:

public slots:

private:
    QSqlDatabase db;
    QSqlQuery  * query;
};

#endif // SQL_H
