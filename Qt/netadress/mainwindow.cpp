#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QIntValidator>
#include <QRegExp>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mac->setInputMask("HH:HH:HH:HH:HH:HH");
    QRegExp re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
    "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QRegExpValidator *rev=new QRegExpValidator(re);
    ui->inux->setValidator(rev);
    QIntValidator *intrev=new QIntValidator(0, 65535);
    ui->windows->setValidator(intrev);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mac_textChanged(const QString &arg1)
{
    qDebug()<<"MAC: "<<arg1;
}

void MainWindow::on_inux_textChanged(const QString &arg1)
{
     qDebug()<<"LINUX: "<<arg1;
}

void MainWindow::on_windows_textChanged(const QString &arg1)
{
    qDebug()<<"WINDOWS: "<<arg1;
}
