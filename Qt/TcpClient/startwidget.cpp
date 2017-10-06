#include "startwidget.h"
#include "ui_startwidget.h"
#include <QHostAddress>
#include <QDebug>
#include <QTcpSocket>
#include <QHostInfo>
#include <QTimer>
#include <QMessageBox>

#define isConnected  (socket->isOpen())

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    setWindowTitle( tr("登录") );

    timer = new QTimer(this);
    socket = new QTcpSocket;

    connect(  socket, &QTcpSocket::connected,
              [=]()
    {
        timer->stop();
        ui->lineIp->setEnabled(false);
    });

    timer->setSingleShot( true );
    connect( timer, &QTimer::timeout,
             [=]()
    {
        QMessageBox::critical(this, tr("失败"), tr("连接服务器失败"));;
    });
}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::on_buttonLogin_clicked()
{
    connectToServer();
    if( isConnected )
    {
        sendMessage(M_Login);
    }
}

void StartWidget::on_buttonRegister_clicked()
{
    connectToServer();
    if( isConnected )
    {
        sendMessage(M_Register);
    }
}

void StartWidget::connectToServer()
{
    //if has not connected, do conncet
    if( !isConnected )
    {
        QString ip = ui->lineIp->text();
        qDebug()<<ip;
        socket->connectToHost( QHostAddress(ip), PORT );
        timer->start( 1000 );
    }
}

void StartWidget::sendMessage(MessageType type)
{
    QString userName = ui->lineUser->text();
    QString passport = ui->linePassport->text();

    if( userName.isEmpty() )
    {
        QMessageBox::information(this, tr("错误"), tr("请输入用户名"));
        return;
    }
    if( passport.isEmpty() )
    {
        QMessageBox::information(this, tr("错误"), tr("请输入密码"));
        return;
    }

    QString message = QString( "%1\n%2\n%3" ).arg( type )
            .arg( userName ).arg( passport );
    socket->write( message.toUtf8() );
}
