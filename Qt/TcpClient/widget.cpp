#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle( tr("Client") );

    connect(&socket, &QTcpSocket::connected, this, &TcpServer::connectSuccess);
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::newMessage()
{
    QString temp( socket.readAll() );
    ui->TextRead->append( temp );
}

void TcpServer::connectSuccess()
{
    ui->TextRead->append( "Connect Success" );
}

void TcpServer::on_buttonSend_clicked()
{
    socket.write( ui->TextWrite->toPlainText().toUtf8() );
    ui->TextWrite->clear();
}

void TcpServer::on_buttonConnect_clicked()
{
}
