#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->_password->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Login_clicked()
{
    if(ui->_username->text().isEmpty()||ui->_password->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Alert"),tr("The username or password is empty, can't login"));
        return;
    }
    D_username=ui->_username->text();
    D_password=QCryptographicHash::hash(ui->_password->text().toUtf8(),QCryptographicHash::Sha3_256);
    QString str=tr("Username: ")+D_username+tr("\r\n")+tr("Password: ");
    str+=D_password.toHex();
    qDebug()<<str;
    QMessageBox::information(this,tr("UserInfo"),str);
}

void MainWindow::on_Logout_clicked()
{
    this->close();
}
