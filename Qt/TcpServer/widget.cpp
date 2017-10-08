#include "widget.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>

//一天
#define USER_INFO_TTL 1000*60*60*24

#define SEND_RET_BACK(Type, UserName)\
{\
    sendRetToUser(Type, socket, UserName);\
    return;\
}

TcpServer::TcpServer(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);
    server->listen( QHostAddress::Any, PORT );

    connect( server, &QTcpServer::newConnection, this, &TcpServer::newConnect);
}

TcpServer::~TcpServer()
{
}

void TcpServer::newConnect()
{
    QTcpSocket *socket = server->nextPendingConnection();
    qDebug()<<socket->peerAddress().toString();
    connect( socket, &QTcpSocket::readyRead,
             [=]()
    {
        QString message (socket->readAll());
        analysisMessage( message, socket);
    });
}

void TcpServer::analysisMessage(QString message, QTcpSocket *socket)
{
    if( message.isEmpty() )
        return;

    int index = message.indexOf("\n");

    MessageType type = static_cast<MessageType>(message.left(index).toInt());
    message = message.mid( index+1, -1 );

    index = message.indexOf("\n");

    if( M_Login == type || M_Register == type )
    {
        QString userName = message.left( index );
        QString passWord = message.mid( index+1 );

//        qDebug()<<userName<<passWord;

        if( M_Login == type )
        {
            MessageType loginStatus = db.login( userName, passWord );
            //login fail. userName don't exist
            if(  M_LoginSuccess == loginStatus )
            {
                qDebug()<<userName<<"Login Success";
                OnlineUser & user = userInfo[userName];
                user.socket = socket;
                user.userName = userName;
            }
            else
            {
                qDebug()<<userName<<"Login Fail";
            }

            SEND_RET_BACK( loginStatus, userName );
        }
        else
        {
            MessageType regStatus = db.insert( userName, passWord );

            if( M_RegisterSuccess ==  regStatus )
            {
                qDebug()<<userName<<"Reg Success";
            }
            else
                qDebug()<<userName<<"Reg Fail";

            SEND_RET_BACK( regStatus, userName  );
        }
    }
    else if( M_Message == type )
    {
        QString fromUserName = message.left( index );
        message = message.mid( index+1, -1 );
        index = message.indexOf("\n");
        QString destUserName = message.left( index );
        QString str = message.mid( index+1 );
        if(   !db.find( destUserName )   )
        {
            SEND_RET_BACK( M_DestNotExist, destUserName );
        }
        OnlineUser & fromUser = userInfo[fromUserName];
        OnlineUser & destUser = userInfo[destUserName];
        if( destUser.socket == nullptr )
        {
            SEND_RET_BACK( M_DestNotOnLine, destUserName );
        }
        sendMsgToUser( fromUser, destUser, str );
        sendRetToUser( M_SendSuccess, socket, "" );
    }
    else if( M_UpdateUserList == type )
    {
        QString msg;
        for_each( userInfo.begin(), userInfo.end(),
                  [&](std::map<QString, OnlineUser>::reference a)
        {
           if( a.second.socket == nullptr )
               msg += '0' + a.second.userName + '\n';
           else
               msg += '1' + a.second.userName + '\n';
        });
        sendRetToUser( M_UpdateUserList, socket, msg );
    }
    else if( M_Logout == type )
    {
        QString userName = message;
        qDebug()<<userName<<"Log Out";
        OnlineUser & user = userInfo[userName];
        user.socket->close();
        //设置为离线状态
        user.socket = nullptr;
        //过一段时间后删除该用户的在线信息
        QTimer::singleShot( USER_INFO_TTL, Qt::VeryCoarseTimer,
                            [userName, this]()
        {
            this->userInfo.erase( userName );
        });
    }
}

void TcpServer::sendMsgToUser(OnlineUser& fromUser, OnlineUser & destUser, QString str)
{
    QString message = QString( "%1\n%2\n%3" ).arg( M_Message )
            .arg( fromUser.userName ).arg( str );
    destUser.socket->write( message.toUtf8() );
}

void TcpServer::sendRetToUser(MessageType ret, QTcpSocket * socket, QString userName)
{
    QString message = QString( "%1\n%2" ).arg( ret )
            .arg(userName);
    socket->write( message.toUtf8() );
}

OnlineUser &TcpServer::findFromUser(QTcpSocket *socket)
{
    for_each( userInfo.begin(), userInfo.end(),
              [=](std::map<QString, OnlineUser>::reference a)
    {
       if( a.second.socket == socket )
           return a.second;
    });
    Q_ASSERT(true);
}
