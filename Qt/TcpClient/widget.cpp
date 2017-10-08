#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QKeyEvent>

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle( tr("Chat") );
    this->setWindowFlags( windowFlags() | Qt::WindowStaysOnTopHint );
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::newMessage(QString temp)
{
    QString msg = temp.mid( temp.indexOf('\n')+1 );
    ui->TextRead->append( msg );
}

void ChatWidget::on_buttonSend_clicked()
{
    QString destName = ui->lineDestName->text();

    QString str( ui->TextWrite->toPlainText().toUtf8() );
    if( str.isEmpty() )
        return;

    QString msg = QString("%1\n%2").arg( destName ).arg( str );
    emit( sendMsg( msg ) );
}

void ChatWidget::keyPressEvent(QKeyEvent *e)
{
    if( (e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Enter )
    {
        on_buttonSend_clicked();
    }
}

void ChatWidget::sendSuccess()
{
    ui->TextWrite->clear();
}

void ChatWidget::on_buttonUpdate_clicked()
{

}
