#ifndef SQL_H
#define SQL_H

#include "../TcpDefines.h"
#include <QObject>
#include <QSqlDatabase>

class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);
    ~Sql();
    MessageType login(const QString name, const QString password);
    MessageType insert(QString name, QString password);
    bool find( QString name );

signals:

public slots:

private:
    QSqlDatabase db;
};

#endif // SQL_H
