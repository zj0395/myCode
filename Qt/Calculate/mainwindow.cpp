#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->inputscreen,SIGNAL(textEdited(QString)),this,SLOT(changeinputstr(QString)));

    connect(this,SIGNAL(newstrchanged(QString)),ui->inputscreen,SLOT(setText(QString)));
    connect(this,SIGNAL(newstrchanged(QString)),this,SLOT(inputkey()));

    connect(this,SIGNAL(resultchanged(QString)),ui->resultscreen,SLOT(setText(QString)));

    connect(this,SIGNAL(presskeydoit()),this,SLOT(changeresultstyle()));

    connect(this,SIGNAL(oldstrchanged()),this,SLOT(tochangeoldstrscreen()));
    connect(this,SIGNAL(oldstrchanged()),this,SLOT(changeinputstyle()));

    connect(this,SIGNAL(oldstr1change(QString)),ui->lastscreen1,SLOT(setText(QString)));
    connect(this,SIGNAL(oldstr2change(QString)),ui->lastscreen2,SLOT(setText(QString)));
    connect(this,SIGNAL(oldstr3change(QString)),ui->lastscreen3,SLOT(setText(QString)));


    reset();
}
void MainWindow::changeinputstr(const QString &str)
{
    if(str.isEmpty()||str[0]=='=')
        return;
    else if(isnotchar(str[str.length()-1]))
        return;
    else
    {
        newstr=str;
        inputkey();
    }
}
bool MainWindow::isnotchar(QChar a)
{
    if((a>='0'&&a<='9')||a=='!'||a=='=')
        return 0;
    else
        return 1;
}

void MainWindow::tochangeoldstrscreen()
{
    if(oldstr1[0]!='E')
    {
        emit oldstr1change(oldstr1);
        emit oldstr2change(oldstr2);
        emit oldstr3change(oldstr3);
    }
}

void MainWindow::changeresultstyle()
{
    QFont ifont("Times New Roman",15);
    QFont rfont("Times New Roman",25);
    ui->resultscreen->setFont(rfont);
    ui->resultscreen->setGeometry(170,80,248,45);
    ui->inputscreen->setFont(ifont);
    ui->inputscreen->setGeometry(170,120,250,30);
}
void MainWindow::changeinputstyle()
{
    QFont rfont("Times New Roman",15);
    QFont ifont("Times New Roman",25);
    ui->inputscreen->setFont(ifont);
    ui->inputscreen->setGeometry(170,110,250,40);
    ui->resultscreen->setFont(rfont);
    ui->resultscreen->setGeometry(170,75,248,40);
}

void MainWindow::inputkey()
{
    if(_needupdate)
    {
        emit oldstrchanged();
        _needupdate=0;
    }

    if(newstr[newstr.length()-1]=='=')
     {  cutthelast(1); on_keydoit_clicked();}
    else
    {
        pushkeynum=1;
        try{
            resultstr.setNum(_calculate::Strcal(newstr).Cal(),'g',6);
            emit resultchanged("="+resultstr);
        }
        catch(QString&ss)
        {
            emit resultchanged(ss);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_keydoit_clicked()
{
    emit presskeydoit();
    if(!pushkeynum)
        return;
    _calculate::Strcal st(newstr);
    emit newstrchanged(newstr+"=");

    try{
        resultstr.setNum(st.Cal(),'g',6);
        const QString &temp=st.WhatIsWrong();
        if(!temp.isEmpty())
            emit oldstr1change(temp);
        else
        {
            setoldstr();
            oldstr1=newstr+"="+resultstr;
            reset();
        }
        emit resultchanged(resultstr);
        _needupdate=1;
    }
    catch(QString&ss)
    {
        setoldstr();
        oldstr1=newstr+ss;
        reset();
        emit resultchanged(ss);
        _needupdate=1;
    }
}

void MainWindow::on_keyadd_clicked()
{
    if(isreset()&&!(resultstr.isEmpty()))
    {
        newstr=resultstr+'+';
        emit newstrchanged(newstr);
    }
    else if(newstr[newstr.size()-1]!='+')
    {
        newstr+='+';
        emit newstrchanged(newstr);
    }
}

void MainWindow::on_keyminus_clicked()
{
    if(isreset()&&!(resultstr.isEmpty()))
     {
        newstr=resultstr+'-';
        emit newstrchanged(newstr);
    }
    else if(newstr[newstr.size()-1]!='-')
    {
        newstr+='-';
        emit newstrchanged(newstr);
    }
}

void MainWindow::on_keymultipy_clicked()
{
    if(isreset()&&!(resultstr.isEmpty()))
    {
        newstr=resultstr+'*';
        emit newstrchanged(newstr);
    }
    else if(newstr[newstr.size()-1]!='*')
    {
        newstr+='*';
        emit newstrchanged(newstr);
    }
}

void MainWindow::on_keydivide_clicked()
{
    if(isreset()&&!(resultstr.isEmpty()))
    {
        newstr=resultstr+'/';
        emit newstrchanged(newstr);
    }
    else if(newstr[newstr.size()-1]!='/')
    {
        newstr+='/';
        emit newstrchanged(newstr);
    }
}

void MainWindow::on_deleteone_clicked()
{
    if( !isreset() )
    {
        int m=newstr.length();
        if( (newstr[m-1]) !='(')
            cutthelast(1);
        else if(m<4)
            cutthelast(1);
        else
        {
            if( newstr[m-3] =='i'||newstr[m-3] =='o'||newstr[m-3] =='a')
                cutthelast(4);
            else if( newstr[m-2]=='n'|| newstr[m-2]=='g' )
                cutthelast(3);
        }
        if(newstr.isEmpty())
            reset();
        emit newstrchanged(newstr);
    }
}

void MainWindow::on_deleteall_clicked()
{
    reset();
    emit newstrchanged(newstr);
}

void MainWindow::on_number3_clicked()
{
    if(isreset())
    {
        newstr="3";
    }
    else
    {
        newstr+='3';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number6_clicked()
{
    if(isreset())
    {
        newstr="6";
    }
    else
    {
        newstr+='6';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number9_clicked()
{
    if(isreset())
    {
        newstr="9";
    }
    else
    {
        newstr+='9';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number8_clicked()
{
    if(isreset())
    {
        newstr="8";
    }
    else
    {
        newstr+='8';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number5_clicked()
{
    if(isreset())
    {
        newstr="5";
    }
    else
    {
        newstr+='5';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number2_clicked()
{
    if(isreset())
    {
        newstr="2";
    }
    else
    {
        newstr+='2';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_keypoint_clicked()
{
    newstr+='.';
    emit newstrchanged(newstr);
}

void MainWindow::on_number0_clicked()
{if(isreset())
    {
        newstr="0";
    }
    else
    {
        newstr+='0';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number1_clicked()
{
    if(isreset())
    {
        newstr="1";
    }
    else
    {
        newstr+='1';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number4_clicked()
{
    if(isreset())
    {
        newstr="4";
    }
    else
    {
        newstr+='4';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_number7_clicked()
{
    if(isreset())
    {
        newstr="7";
    }
    else
    {
        newstr+='7';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_leftbracket_clicked()
{
    if(isreset())
    {
        newstr="(";
    }
    else
    {
        newstr+='(';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_rightbracket_clicked()
{
    if(isreset())
    {
        newstr=")";
    }
    else
    {
        newstr+=')';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_num10_clicked()
{
    if(isreset())
    {
        newstr="e";
    }
    else
    {
        newstr+='e';
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_CONSTPI_clicked()
{
    if(isreset())
    {
        newstr="π";
    }
    else
    {
        newstr+="π";
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_sqrt_clicked()
{
    if(isreset())
    {
        newstr="√";
    }
    else
    {
        newstr+="√";
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_power_clicked()
{
    if(newstr[newstr.size()-1]!='^')
    {
        newstr+='^';
        emit newstrchanged(newstr);
    }
}

void MainWindow::on_calfact_clicked()
{
    newstr+='!';
    emit newstrchanged(newstr);
}

void MainWindow::on_calsin_clicked()
{
    if(isreset())
    {
        newstr="sin(";
    }
    else
    {
        newstr+="sin(";
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_calcos_clicked()
{
    if(isreset())
    {
        newstr="cos(";
    }
    else
    {
        newstr+="cos(";
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_caltan_clicked()
{
    if(isreset())
    {
        newstr="tan(";
    }
    else
    {
        newstr+="tan(";
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_calln_clicked()
{
    if(isreset())
    {
        newstr="ln(";
    }
    else
    {
        newstr+="ln(";
    }
    emit newstrchanged(newstr);
}

void MainWindow::on_callg_clicked()
{
    if(isreset())
    {
        newstr="lg(";
    }
    else
    {
        newstr+="lg(";
    }
    emit newstrchanged(newstr);
}
