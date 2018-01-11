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

    this->setWindowTitle( tr("工程项目风险识别系统") );

    mainWidget = new Form_MainWidget;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QPoint nowPos = this->pos();

    int centerX = nowPos.x();
    int centerY = nowPos.y();

    this->close();

    QDesktopWidget *deskWgt = QApplication::desktop();
    if (deskWgt)
    {
        int virtualWidth  = deskWgt->width();
        int virtualHeight = deskWgt->height();

        int width         = mainWidget->width();
        int height        = mainWidget->height();

        centerX = centerX + width  > virtualWidth  ? virtualWidth  - width  : centerX;
        centerY = centerY + height > virtualHeight ? virtualHeight - height : centerY;
    }

    mainWidget->move( centerX, centerY );
    mainWidget->show();
}

void Widget::on_pushButton_2_clicked()
{
    exit(0);
}
