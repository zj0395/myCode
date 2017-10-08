#include "startwidget.h"
#include "ui_startwidget.h"
#include <QHostAddress>
#include <QDebug>
#include <QTcpSocket>
#include <QHostInfo>
#include <QTimer>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

#define DEFAULT_IP  "101.200.144.41"


StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    this->setWindowFlags( windowFlags() | Qt::WindowStaysOnTopHint );
    ui->lineIp->setText(DEFAULT_IP);
    setWindowTitle( tr("登录") );
    isConnected = false;

    timer = new QTimer(this);
    socket = new QTcpSocket;
    timer->setSingleShot( true );

    connect( socket, &QTcpSocket::readyRead, this, &StartWidget::recvMessage );

    connect(  socket, &QTcpSocket::connected, this, &StartWidget::connectedToServer);

    connect( timer, &QTimer::timeout, this, &StartWidget::timeOut);

    connect( &chatWidget, &ChatWidget::sendMsg, this, &StartWidget::sendMessage );
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
        sendInfo(M_Login);
    }
}

void StartWidget::on_buttonRegister_clicked()
{
    connectToServer();
    if( isConnected )
    {
        sendInfo(M_Register);
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

void StartWidget::sendInfo(MessageType type)
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

void StartWidget::sendMessage(QString msg)
{
    QString message = QString( "%1\n%2" ).arg( M_Message )
            .arg( msg );
    socket->write( message.toUtf8() );
}

void StartWidget::recvMessage()
{
    QString message( socket->readAll() );

    int index = message.indexOf( '\n' );
    MessageType type = static_cast<MessageType>(message.left(index).toInt());
    message = message.mid( index+1 );
    qDebug()<<"type"<<type;

    switch (type)
    {
    case M_WrongUserName:
        showWrong( tr("错误"), tr("用户名不存在") );
        break;
    case M_WrongPassword:
        showWrong( tr("错误"), tr("密码错误") );
        break;
    case M_UserNameExist:
        showWrong( tr("错误"), tr("该用户名已存在") );
        break;
    case M_DestNotExist:
        showWrong( tr("错误"), tr("用户不存在") );
        break;
    case M_DestNotOnLine:
        showWrong( tr("错误"), tr("用户不在线") );
        break;
    case M_Message:
        showMessage(message);
        break;
    case M_LoginSuccess:
        this->close();
        chatWidget.show();
        break;
    case M_RegisterSuccess:
        showInfomation( tr("成功"), tr("注册成功"));
        break;
    case M_SendSuccess:
        chatWidget.sendSuccess();
        break;
    default:
        break;
    }
}

void StartWidget::showWrong(QString title, QString word)
{
    QMessageBox::critical( this, title, word);
}

void StartWidget::showInfomation(QString title, QString word)
{
    QMessageBox::information( this, title, word);
}

void StartWidget::connectedToServer()
{
    timer->stop();
    ui->lineIp->setEnabled(false);
    isConnected = true;
}
void StartWidget::timeOut()
{
    if( !isConnected )
    {
        QMessageBox::critical(this, tr("失败"), tr("连接服务器失败"));;
    }
}

void StartWidget::showMessage(QString msg)
{
    chatWidget.newMessage(msg);
}
