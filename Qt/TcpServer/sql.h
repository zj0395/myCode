#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlDatabase>

class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);
    bool login(QString name, QString password);

signals:

public slots:

private:
    QSqlDatabase db;
};

#endif // SQL_H
