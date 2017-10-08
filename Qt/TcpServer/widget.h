#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QTcpServer>
#include <map>
#include <QString>
#include "sql.h"
#include "../TcpDefines.h"

struct User
{
    QString userName;
    QString passWord;
    QTcpSocket* socket;
};

class TcpServer : public QObject
{
    Q_OBJECT
    typedef std::map<QString, User> MStrToUser;

public:
    TcpServer(QObject *parent = 0);
    ~TcpServer();

private:
    QTcpServer * server;
//    Sql db;
    MStrToUser userInfo;

private:
    void newConnect();
    void analysisMessage(QString , QTcpSocket *socket);
    void sendMsgToUser(User &, User&, QString );
    void sendRetToUser(MessageType, QTcpSocket *, QString );
    User& findFromUser(QTcpSocket* socket);
};

#endif // WIDGET_H
