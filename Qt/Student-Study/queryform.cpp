#include "queryform.h"
#include "ui_queryform.h"
#include "dialoghelp.h"

QueryForm::QueryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryForm)
{
    ui->setupUi(this);

    sql = Sql::getSql();
}

QueryForm::~QueryForm()
{
    delete ui;
}

void QueryForm::on_butonGet_clicked()
{
    QString idiom = ui->lineInput->text();

    QString explain;

    switch ( sql->getInformation( idiom, explain ) ) {
    case M_WrongUserName:
        INFORMATION( tr("提示"), tr("未查询到该成语") );
        break;
    case M_LoginSuccess:
        INFORMATION( tr("提示"), tr("查询成功") );
        ui->textBrowser->setText( explain );
        break;
    default:
        break;
    }
}

void QueryForm::on_buttonSet_clicked()
{
    QString idiom = ui->lineInput->text();

    QString explain = ui->textBrowser->toPlainText();

    switch ( sql->setInformation( idiom, explain ) ) {
    case M_SqlInsertWrong:
        INFORMATION( tr("提示"), tr("插入失败") );
        break;
    case M_RegisterSuccess:
        INFORMATION( tr("提示"), tr("插入成功") );
        break;
    case M_UserNameExist:
        INFORMATION( tr("提示"), tr("该成语已存在") );
        break;
    default:
        break;
    }
}
