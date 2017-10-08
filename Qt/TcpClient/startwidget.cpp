#include "startwidget.h"
#include "ui_startwidget.h"
#include <QHostAddress>
#include <QDebug>
#include <QTcpSocket>
#include <QHostInfo>
#include <QTimer>
#include <QMessageBox>
#include <QTime>

#pragma execution_character_set("utf-8")

//#define DEFAULT_IP  "127.0.0.1"
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

    connect( socket, &QTcpSocket::connected, this, &StartWidget::connectedToServerSuccess);

    connect( timer, &QTimer::timeout, this, &StartWidget::timeOut);

    //发送消息
    connect( &chatWidget, &ChatWidget::sendMsg,
             [=](QString fromUser, QString msg)
    {
        this->sendMessage( M_Message, fromUser + '\n' + msg );
    });
    //更新用户列表
    connect( &chatWidget, &ChatWidget::sendUpdateUserMsg,
             [=]()
    {
        this->sendMessage( M_UpdateUserList, "" );
    });
    //退出
    connect( &chatWidget, &ChatWidget::sendCloseMsg,
             [=](QString userName)
    {
        this->sendMessage( M_Logout, userName );
        //解决网速较慢时不能正常退出的问题
        QTime dieTime = QTime::currentTime().addMSecs(100);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        this->socket->close();
    });
}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::on_buttonLogin_clicked()
{
    task = Task_Login;
    connectToServer();
    if( isConnected )
    {
        sendUserInfo(M_Login);
    }
}

void StartWidget::on_buttonRegister_clicked()
{
    task = Task_Reg;
    connectToServer();
    if( isConnected )
    {
        sendUserInfo(M_Register);
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

void StartWidget::sendUserInfo(MessageType type)
{
    QString userName = ui->lineUser->text();
    QString password = ui->linePassport->text();

    if( userName.isEmpty() )
    {
        QMessageBox::information(this, tr("错误"), tr("请输入用户名"));
        return;
    }
    if( password.isEmpty() )
    {
        QMessageBox::information(this, tr("错误"), tr("请输入密码"));
        return;
    }

    sendMessage( type, userName + '\n' + password );
}

void StartWidget::sendMessage(MessageType type, QString msg)
{
    QString message = QString( "%1\n%2" ).arg( type )
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
        showWrongChatWindow( tr("错误"), tr("用户不存在") );
        break;
    case M_DestNotOnLine:
        showWrongChatWindow( tr("错误"), tr("用户不在线") );
        break;
    case M_Message:
        chatWidget.newMessage(message);
        break;
    case M_LoginSuccess:
        this->close();
        chatWidget.show();
        chatWidget.setUserName(message);
        break;
    case M_RegisterSuccess:
        showInfomation( tr("成功"), tr("注册成功"));
        break;
    case M_SendSuccess:
        chatWidget.sendSuccess();
        break;
    case M_UpdateUserList:
        chatWidget.updateUserList(message);
        break;
    default:
        break;
    }
}

void StartWidget::showWrong(QString title, QString word)
{
    QMessageBox::critical( this, title, word);
}

void StartWidget::showWrongChatWindow(QString title, QString word)
{
    QMessageBox::critical( &chatWidget, title, word);
}

void StartWidget::showInfomation(QString title, QString word)
{
    QMessageBox::information( this, title, word);
}

void StartWidget::connectedToServerSuccess()
{
    timer->stop();
    ui->lineIp->setEnabled(false);
    isConnected = true;

    if( Task_Login == task )
        on_buttonLogin_clicked();
    else if( Task_Reg == task )
        on_buttonRegister_clicked();
}

void StartWidget::timeOut()
{
    if( !isConnected )
    {
        showWrong(tr("失败"), tr("连接服务器失败"));
    }
}
