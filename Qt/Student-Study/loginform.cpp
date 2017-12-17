#include "loginform.h"
#include "ui_mainform.h"
#include "dialoghelp.h"
#include "queryform.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    ui->linePassword->setEchoMode(QLineEdit::Password);

    queryForm = new QueryForm;

    sql = Sql::getSql();
}

LoginWidget::~LoginWidget()
{
    delete ui;
    delete queryForm;
}

void LoginWidget::on_buttonLogin_clicked()
{
    QString userName = ui->lineUsername->text();
    QString password = ui->linePassword->text();

    CHECK_EMPTY( userName, "用户名" );
    CHECK_EMPTY( password, "密码" );

    switch ( sql->login( userName, password ))  {
    case M_LoginSuccess:
        INFORMATION( tr("提示"), tr("登录成功")  );
        close();
        queryForm->show();
        break;
    case M_WrongPassword:
        INFORMATION( tr("提示"), tr("密码错误")  );
        break;
    case M_WrongUserName:
        INFORMATION( tr("提示"), tr("用户名不存在")  );
        break;
    default:
        break;
    }
}

void LoginWidget::on_buttonReg_clicked()
{
    QString userName = ui->lineUsername->text();
    QString password = ui->linePassword->text();

    CHECK_EMPTY( userName, "用户名" );
    CHECK_EMPTY( password, "密码" );

    switch ( sql->insert( userName, password ) ) {
    case M_RegisterSuccess:
        INFORMATION( tr("提示"), tr("注册成功")  );
        break;
    case M_UserNameExist:
        INFORMATION( tr("提示"), tr("用户名已存在")  );
        break;
    default:
        INFORMATION( tr("提示"), tr("注册失败")  );
        break;
    }
}
