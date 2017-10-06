#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QTcpServer>
#include <map>
#include <QString>
#include "sql.h"

class TcpServer : public QObject
{
    Q_OBJECT
    typedef std::map<QString, QTcpSocket *> MStrToSocket;

public:
    TcpServer(QObject *parent = 0);
    ~TcpServer();

private:
    QTcpServer * server;
    Sql db;
    MStrToSocket userInfo;

private:
    void newConnect();
    void analysisMessage( QString );
};

#endif // WIDGET_H
