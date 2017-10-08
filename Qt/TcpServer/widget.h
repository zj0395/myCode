#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QTcpServer>
#include <map>
#include <QString>
#include "sql.h"
#include "../TcpDefines.h"

struct OnlineUser
{
    OnlineUser(){socket=nullptr;}
    QString userName;
    QTcpSocket* socket;
};

class TcpServer : public QObject
{
    Q_OBJECT
    typedef std::map<QString, OnlineUser> MStrToUser;

public:
    TcpServer(QObject *parent = 0);
    ~TcpServer();

private:
    QTcpServer * server;
    Sql db;
    MStrToUser userInfo;

private:
    void newConnect();
    void analysisMessage(QString , QTcpSocket *socket);
    void sendMsgToUser(OnlineUser &, OnlineUser&, QString );
    void sendRetToUser(MessageType, QTcpSocket *, QString );
    OnlineUser& findFromUser(QTcpSocket* socket);
};

#endif // WIDGET_H
