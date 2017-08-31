#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTableView>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFontDialog>
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <iostream>

static int x_t=0,y_t=0;
static QFont ft1("宋体",13);
static QFont ft2("Times New Roman",13);
static QFont ft3("Times New Roman",11);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),vvnum( 9 , vint(9,0) )
{
    ui->setupUi(this);
    widget = new QWidget();
    this->setWindowTitle(tr("数独求解器"));
    this->setCentralWidget(widget);
    widget2 = new QFrame(this);
    QGridLayout* gl = new QGridLayout(widget);
    b= new QPushButton**[9];
    for(int i=0 ;i<9 ;++i)
    {
        b[i]=new QPushButton*[9];
        for( int j=0;j<9;++j)
        {
            b[i][j]=new QPushButton;
            b[i][j]->setMinimumSize(40,40);
            b[i][j]->setFont(ft2);
            gl->addWidget(b[i][j],i,j);
            b[i][j]->setAccessibleName(QString::number(i*10+j));
            connect(b[i][j],SIGNAL(clicked()),this,SLOT(tablebuttonClicked()));
            b[i][j]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        }
    }
    gl->setMargin(50);
    gl->setVerticalSpacing(1);
    gl->setHorizontalSpacing(1);
    others=new QPushButton*[3];
    QString str[3]={("开始求解"),("清空全部"),("规则简介")};
    for( int i =0 ;i<3; ++i)
    {
        others[i]=new QPushButton(str[i]);
        others[i]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        others[i]->setMinimumSize(80,40);
        gl->addWidget(others[i] ,9,1+i*3,1,2);
    }
    for(int i=0;i<9;++i)
    {
        gl->setColumnStretch(i,1);
        gl->setRowStretch(i,1);
    }
    gl->setRowStretch(9,1);
    widget->setMinimumSize(380,480);
    this->setMinimumSize(480,520);

    connect(others[0],SIGNAL(clicked(bool)),this,SLOT(beginclicked()));
    connect(others[1],SIGNAL(clicked(bool)),this,SLOT(new_tabclicked()));
    connect(others[2],SIGNAL(clicked(bool)),this,SLOT(about_clicked()));


    QGridLayout* gl2 = new QGridLayout;
    key=new QPushButton*[10];
    QString a;
    for(int i=0;i<9;++i)
    {
        key[i]=new QPushButton(a.setNum(i+1));
        key[i]->setFont(ft3);
        gl2->addWidget(key[i],i/3,i%3,Qt::AlignCenter|Qt::AlignHCenter);
        key[i]->setMinimumSize(40,38);
        connect(key[i],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));
    }
    key[9]=new QPushButton(tr("C"));
    QPalette pal;
    pal.setColor(QPalette::ButtonText,QColor("#ff0000"));
    key[9]->setPalette(pal);
    gl2->addWidget(key[9],3,1,Qt::AlignCenter|Qt::AlignHCenter);
    key[9]->setMinimumSize(40,40);
    key[9]->setFont(ft3);
    for( int i=0 ; i<3; ++i)
    {
        gl2->setRowStretch(i,1);
        gl2->setColumnStretch(i,1);
    }
    gl2->setRowStretch(3,1);
    connect(key[9],SIGNAL(clicked(bool)),this,SLOT(keyboardclicked()));

    gl2->setSpacing(0);
    widget2->setMinimumSize(120,160);
    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    widget2->setLayout(gl2);
    widget2->close();

    setButtonInit();

    this->resize( 520,570);

    int wid=this->width();
    int hei=this->height();
    //获取设备屏幕大小
    QRect screenRect = QApplication::desktop()->screenGeometry();
    int wid2=screenRect.width();
    int hei2=screenRect.height();
    if( screenRect.height() >1040 )
    {
        double scale=double(hei2)/1080;
        wid*=scale;
        hei*=scale;
    }
    this->setMaximumSize(  double(hei2)/hei*wid  , hei2   );
    this->setGeometry(     (wid2-wid)/3 ,(hei2-hei)/7  ,wid ,hei  );
}
void MainWindow::resizeEvent(QResizeEvent *)
{
    widget2->show();
    widget2->resize( 1.0*widget->width()/520*120  , 1.0*widget->height()/570*160  );
    int a=widget2->width()/3;
    int b=widget2->height()/4;
    for( int i=0 ; i<10 ;++i)
    {
        key[i]->resize(a,b);
    }
    key[9]->resize(a-2,b-2);
    widget2->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tablebuttonClicked()
{
    QPushButton*btn = qobject_cast<QPushButton*>(sender());
    int n=btn->accessibleName().toInt();
    int i=n/10,j=n%10;
    x_t=i;y_t=j;
    QRect r1=btn->geometry();
    int xa=b[0][0]->width();
    int m1=  widget2->width() ;
    int m2=  widget2->height() ;
    if(  this->height()-r1.y()-10  > m2 )
        widget2->move( r1.x()-(m1-xa)/2-3 ,  r1.y()+10  );
    else
        widget2->move( r1.x()-(m1-xa)/2-3 ,  this->height()-m2 );
    widget2->show();
}

void MainWindow::keyboardclicked()
{
    QPushButton*btn = qobject_cast<QPushButton*>(sender());
    vvnum[x_t][y_t]=btn->text().toInt();
    if(vvnum[x_t][y_t])
    {
        b[x_t][y_t]->setText(  btn->text()  );
        b[x_t][y_t]->setStyleSheet(  "background-color: #A2B5CD;" );//008f62 1d86ae b3de69
    }
    else
    {
        b[x_t][y_t]->setText("");
        b[x_t][y_t]->setStyleSheet(  "background-color: #ffffff;" );
    }
    widget2->close();
}
void MainWindow::setButtonInit()
{
    static char a1[] =  "background-color: #A2B5CD;" ;
    static char a2[] =  "background-color: #ffffff;" ;
    char*bs=nullptr;
    for(int i=0 ;i<9 ;++i)
    {
        for( int j=0;j<9;++j)
        {
            bs = vvnum[i][j] ? a1 : a2;
            b[i][j]->setStyleSheet(bs);
        }
    }
}
void MainWindow::about_clicked()
{
    widget2->close();
    QMessageBox::information(this,tr("简介"),tr("本软件会根据已有数字生成数独的解，如果已有数字太少，则数独可能会有多个解，但本软件只会随机生成出一个可行解。\n"
                                              "关于唯一解\n一个好的数独应该有且仅有唯一解，唯一解的一个必要条件是："
                                              "1-9之间9个数字都应该至少有8个在9×9方格中出现。同样的条件多次点击“开始求解”可验证自己的数独是否有唯一解。关于唯一解更详细的介绍可以自行百度。\n"));
}

void MainWindow::beginclicked()
{
    widget2->close();
    SudokuCrack s(vvnum);
    int n=s.beginCrack();
    if(n<0)
    {
        static QString s[3]{("行"),("列"),("3×3方格")};
        QMessageBox::critical(this,tr("数独非法！"),tr("原因：在某%1上有重复数字！").arg(s[n+3]));
        return;
    }
    qDebug()<<n;
    const vvint &d=s.getResult();
    if( n!= 1)
    {
        QMessageBox::critical(this,tr("求解失败!"),tr("该数独无唯一解！"));
    }
    else
    {
        QMessageBox::information(this,tr("成功求解！"),tr("所求解将在屏幕上显示"));
        setResult(d);
    }
}
void MainWindow::new_tabclicked()
{
    vvint d( 9 ,vint(9,0));
    using std::swap;
    swap(d,vvnum);
    setButtonInit();
    clearall();
}
void MainWindow::setResult(const vvint&d)
{
    QString a;
    for(int i=0 ;i<9 ;++i)
    {
        for( int j=0;j<9;++j)
        {
            b[i][j]->setText(a.setNum(d[i][j]));
        }
    }
}
void MainWindow::clearall()
{
    widget2->close();
    for(int i=0 ;i<9 ;++i)
    {
        for( int j=0;j<9;++j)
        {
            vvnum[i][j]=0;
            b[i][j]->setText("");
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    int bm=ui->menuBar->geometry().bottom();
    QPainter p(this);
    QPen ss;
    ss.setWidth(2);
    ss.setColor(Qt::red);
    p.setPen(ss);

    for( int i=3 ; i<8; i+=3)
    {
        int x1= (b[0][i]->geometry().left()+b[0][i-1]->geometry().right())/2;
        int y1= b[0][i]->geometry().top();
        int y2=b[8][i]->geometry().bottom();
        p.drawLine( x1+1 ,y1+2+bm,x1+1,y2+bm );
    }
    for( int i=3 ; i<8; i+=3)
    {
        int y1= (b[i][0]->geometry().top()+b[i-1][0]->geometry().bottom())/2;
        int x1= b[i][0]->geometry().left();
        int x2=b[i][8]->geometry().right();
        p.drawLine( x1+2 ,y1+1+bm,x2-2,y1+1+bm );
    }
}

void MainWindow::on_action_triggered()
{
    bool ok=false;
    QFont font = QFontDialog::getFont(&ok,ft2,this,tr("数字字体选择"));
    if(ok)
    {
        ft2=font;
        for(int i=0 ;i<9 ;++i)
        {
            for( int j=0;j<9;++j)
            {
                b[i][j]->setFont(font);
            }
        }
    }
}

void MainWindow::on_action_2_triggered()
{
    bool ok=false;
    QFont font = QFontDialog::getFont(&ok,ft3,this,tr("数字字体选择"));
    if(ok)
    {
        ft3=font;
        for(int i=0 ;i<10 ;++i)
        {
            key[i]->setFont(font);
        }
    }
}

void MainWindow::on_action_3_triggered()
{
    bool ok=false;
    QFont font = QFontDialog::getFont(&ok,ft1,this,tr("中文字体选择"));
    if(ok)
    {
        ft1=font;
        for(int i=0 ;i<3 ;++i)
        {
            others[i]->setFont(font);
        }
    }
}

void MainWindow::on_action_4_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,tr("选择文件"));
    if(path.isEmpty())
        return;
    std::ifstream file( path.toStdString().c_str() );
    std::ofstream ofile("data_SudokuCrack");
    std::string str;
    std::stringstream ss;
    char temp[9][9];
    vvint vvnumTemp( 9 , vint(9,0));
    int times = 0;
    timeval s1;
    timeval s2;
    timeval s3;
    timeval s4;
    gettimeofday(&s1,NULL);
    while(getline(file,str))
    {
        ss<<str;
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                ss>>temp[i][j];
                vvnumTemp[i][j] = temp[i][j]-48;
                std::cout<<vvnumTemp[i][j];
            }
        }
        std::cout<<std::endl;
        gettimeofday(&s4,NULL);
        SudokuCrack s(vvnumTemp);
        ++times;
        int n=s.beginCrack();
        gettimeofday(&s3,NULL);
        qDebug()<<"Times: "<<times<<" take time: "<< (double (s3.tv_sec-s4.tv_sec)*1000+(s3.tv_usec-s4.tv_usec)/1000)<<"msec";
        if(n<0)
        {
            static QString s[3]{("行"),("列"),("3×3方格")};
            QMessageBox::critical(this,tr("数独非法！"),tr("原因：在某%1上有重复数字！").arg(s[n+3]));
            return;
        }
        const vvint d=s.getResult();
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                ofile<<d[i][j];
            }
        }
        ofile<<"\n";
        gettimeofday(&s4,NULL);
    }
    gettimeofday(&s2,NULL);
    qDebug()<<"All Times: "<<times<<" take time: "<< (double (s2.tv_sec-s1.tv_sec)*1000000+s2.tv_usec-s1.tv_usec)/1000000<<"sec";
    ofile.close();
    file.close();
}
