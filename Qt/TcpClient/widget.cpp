#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QStringList>
#include <QMessageBox>

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle( tr("Chat") );
//    this->setWindowFlags( windowFlags() | Qt::WindowStaysOnTopHint );

    userModel = new QStandardItemModel;
    ui->userList->setModel( userModel );
    ui->userList->setWindowTitle( tr("用户列表") );
    userModel->setHorizontalHeaderLabels( QStringList(tr("用户名")) << tr("是否在线") );

    timer = new QTimer;

    connect(timer, &QTimer::timeout,
            [this]()
    {
        this->on_buttonUpdate_clicked();
    });
}

void ChatWidget::setUserName(QString name)
{
    userName = name;
    on_buttonUpdate_clicked();
    //每一分钟自动更新一次列表
    timer->start(1000*60);
}

void ChatWidget::updateUserList(QString list)
{
    userModel->clear();
    userModel->setHorizontalHeaderLabels( QStringList(tr("用户名")) << tr("是否在线") );
    userModel->setColumnCount(2);
    int index = 0;
    while( ( index = list.indexOf('\n') ) != -1 )
    {
        QString info = list.left( index );
        QString online;
        list = list.mid( index+1 );
        if( '0' == info[0] )
            online = "No";
        else
            online = "Yes";
        QList<QStandardItem*> list;
        list.append( new QStandardItem(info.mid(1)) );
        list.append( new QStandardItem(online) );
        foreach (QStandardItem* item, list) {
            item->setTextAlignment(Qt::AlignCenter);
            item->setEditable(false);
        }
        userModel->insertRow( userModel->rowCount(), list);
    }
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::newMessage(QString temp)
{
    QString fromUser = temp.left( temp.indexOf('\n') );
    QString msg = temp.mid( temp.indexOf('\n')+1 );
    ui->TextRead->append( fromUser + ":\n" + msg );
}

void ChatWidget::on_buttonSend_clicked()
{
    QString destName = ui->lineDestName->text();

    QString str( ui->TextWrite->toPlainText().toUtf8() );
    if( str.isEmpty() )
        return;

    QString msg = QString("%1\n%2").arg( destName ).arg( str );
    if( destName == userName )
    {
        newMessage(msg);
        sendSuccess();
        return;
    }

    emit( sendMsg( userName, msg ) );
}

void ChatWidget::keyPressEvent(QKeyEvent *e)
{
    if( (e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Enter )
    {
        on_buttonSend_clicked();
    }
}

void ChatWidget::closeEvent(QCloseEvent *)
{
    timer->stop();
    delete timer;
    emit( sendCloseMsg(userName) );
}

void ChatWidget::sendSuccess()
{
    ui->TextWrite->clear();
}

void ChatWidget::on_buttonUpdate_clicked()
{
    emit( sendUpdateUserMsg() );
}

void ChatWidget::on_buttonNothing_clicked()
{
    QMessageBox::information(this, tr("不知道该显示啥"), tr("这个按钮不知道该用来干啥\n就随便显示显示\n"
                                                     "wqfjw9aiojgihwaitrua\n"
                                                     "sapkgpioewqurwqiru\n"
                                                     "218934721987218598631hyoasjhf\n"));
}
