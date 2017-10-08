#include "widget.h"
#include <QHostAddress>
#include <QTcpSocket>


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
        qDebug()<<userName<<passWord;
        if( M_Login == type )
        {
            qDebug()<<"logib";
//            db.login( userName, passWord );
            //login fail. userName don't exist
            if( userInfo.find( userName ) == userInfo.end() )
            {
                SEND_RET_BACK( M_WrongUserName, userName );
            }
            User & user = userInfo[userName];
            if( passWord == user.passWord )
            {
                user.socket = socket;
                SEND_RET_BACK( M_LoginSuccess, userName  );
            }
            else
            {
                SEND_RET_BACK( M_WrongPassword, userName  );
            }
        }
        else
        {
            //register fail. userName exist
            if( userInfo.find( userName ) != userInfo.end() )
            {
                SEND_RET_BACK( M_UserNameExist, userName );
            }
            User & user = userInfo[userName];
            user.userName = userName;
            user.passWord = passWord;
            SEND_RET_BACK( M_RegisterSuccess, userName  );
        }
    }
    else if( M_Message == type )
    {
        QString destUserName = message.left( index );
        QString str = message.mid( index+1 );
        if( userInfo.find( destUserName ) == userInfo.end() )
        {
            SEND_RET_BACK( M_DestNotExist, destUserName );
        }
//        User fromUser = findFromUser(socket);
        User & destUser = userInfo[destUserName];
        if( destUser.socket == nullptr )
        {
            SEND_RET_BACK( M_DestNotOnLine, destUserName );
        }
        sendMsgToUser( destUser, destUser, str );
        sendRetToUser( M_SendSuccess, socket, "" );
    }
}

void TcpServer::sendMsgToUser(User& fromUser, User & destUser, QString str)
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

User &TcpServer::findFromUser(QTcpSocket *socket)
{
    for_each( userInfo.begin(), userInfo.end(),
              [=](std::map<QString, User>::reference a)
    {
       if( a.second.socket == socket )
           return a.second;
    });
    Q_ASSERT(true);
}
