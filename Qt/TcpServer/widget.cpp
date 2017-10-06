#include "widget.h"
#include <QHostAddress>
#include <QTcpSocket>
#include "../TcpDefines.h"

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
        analysisMessage( message );
    });
}

void TcpServer::analysisMessage(QString message)
{
    if( message.isEmpty() )
        return;
    MessageType type = static_cast<MessageType>(message.left(1).toInt());
    message = message.mid( 2, -1 );

    int index = message.indexOf("\n");

    if( M_Login == type || M_Register == type )
    {
        QString userName = message.left( index );
        QString passport = message.mid( index+1 );
        qDebug()<<userName<<passport;
        if( M_Login == type )
        {
        }
        else
        {
        }
    }
    else if( M_Message == type )
    {
        QString destUser = message.left( index );
    }
}
