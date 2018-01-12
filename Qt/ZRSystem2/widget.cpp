#include "widget.h"
#include "ui_widget.h"
#include "form_mainwidget.h"
#include <QDebug>
#include <QDesktopWidget>

# pragma execution_character_set("utf-8")//可以使用中文

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle( tr("工程风险预防方案选择系统") );

    mainWidget = new Form_MainWidget;
}

Widget::~Widget()
{
    delete ui;
}

void moveWidget( QWidget * widget, QPoint nowPos )
{
    int centerX = nowPos.x();
    int centerY = nowPos.y();

    QDesktopWidget *deskWgt = QApplication::desktop();
    if (deskWgt)
    {
        int virtualWidth  = deskWgt->width();
        int virtualHeight = deskWgt->height();

        int width         = widget->width();
        int height        = widget->height();

        centerX = centerX + width  > virtualWidth  ? virtualWidth  - width  : centerX;
        centerY = centerY + height > virtualHeight ? virtualHeight - height : centerY;
    }

    widget->move( centerX, centerY );
}

void Widget::on_pushButton_clicked()
{
    QPoint nowPos = this->pos();

    this->close();

    moveWidget( mainWidget, nowPos );
    mainWidget->show();
}

void Widget::on_pushButton_2_clicked()
{
    exit(0);
}
