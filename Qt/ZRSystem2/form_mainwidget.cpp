#include "form_mainwidget.h"
#include <QGridLayout>
#include <QStandardItem>
#include <QLabel>
#include <QDebug>
#include <QRadioButton>
#include <QPushButton>

# pragma execution_character_set("utf-8")//可以使用中文


const VQString show1Str = { "损失成本",
                            "发生概率",
                            "工期影响",
                            "质量影响",
                            "综合评价结果"};

const VQString show2Str = { "预防成本",
                            "发生概率",
                            "工期影响",
                            "质量影响"};

QLabel* newLabel(QString str)
{
    QLabel * label = new QLabel(str);
    label->setAlignment( Qt::AlignHCenter );
    return label;
}


Form_MainWidget::Form_MainWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle( "工程风险预防方案选择系统" );

    QTabWidget * mainWidget = new QTabWidget;
    mainWidget->addTab(  getFirstWidget(), "总设置");
    mainWidget->addTab(  getPlanWidget(),  "方案选择");


    QVBoxLayout * vlayout  = new QVBoxLayout;
    QRadioButton* ratioBut = new QRadioButton("空行视为0");
    QPushButton * buttonDo = new QPushButton("开始计算");
    vlayout->addStretch();
    vlayout->addWidget(ratioBut);
    vlayout->addWidget(buttonDo);
    vlayout->addStretch();

    connect( ratioBut, &QPushButton::clicked,
             [=](bool sta)
    {
        b_checkEmptyLine = sta;
    });
    connect( buttonDo, &QPushButton::clicked,
             [=]()
    {
        doCalculate();
    });


    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget( mainWidget, 0, 0 );
    layout->addLayout( vlayout, 0, 1 );

    resize( 500, 250 );

    b_checkEmptyLine = false;
}


QWidget* Form_MainWidget::getFirstWidget()
{
    QWidget * widget = new QWidget;
    QGridLayout * layout = new QGridLayout( widget );

    QLabel * label1 = newLabel("风险事件");
    label1->setMaximumHeight( 30 );
    layout->addWidget( label1, 0, 1 );
    for( int j=0; j<show1Str.size(); ++j )
    {
        QLabel   * label   = newLabel(show1Str[j]);
        QLineEdit* lienA   = new QLineEdit;

        layout->addWidget( label, j+1, 0 );
        layout->addWidget( lienA, j+1, 1 );

        edits[0].push_back(   lienA );
    }
    return widget;
}

bool Form_MainWidget::checkEmpty()
{
    return true;
}

void Form_MainWidget::doCalculate()
{
    qDebug()<<b_checkEmptyLine;
    if( b_checkEmptyLine )
    {
        if( ! checkEmpty() )
            return;
    }
}


QWidget* Form_MainWidget::getPlanWidget()
{
    QTabWidget* tab = new QTabWidget;

    for( int i=0; i<PLAN_NUMBER; ++i )
    {
        QWidget * widget = new QWidget;
        QGridLayout * w2_layout = new QGridLayout( widget );

        QLabel * label1 = newLabel("风险量");
        QLabel * label2 = newLabel("权重");
        label1->setMaximumHeight( 30 );
        w2_layout->addWidget( label1, 0, 0, 1, 2 );
        w2_layout->addWidget( label2, 0, 2, 1, 1 );

        for( int j=0; j<show2Str.size(); ++j )
        {
            QLabel   * label   = newLabel(show2Str[j]);
            QLineEdit* lienA   = new QLineEdit;
            QLineEdit* lienWei = new QLineEdit;

            w2_layout->addWidget( label,   j+1, 0 );
            w2_layout->addWidget( lienA,   j+1, 1 );
            w2_layout->addWidget( lienWei, j+1, 2 );

            edits[i+1].push_back(   lienA );
            edits[i+2].push_back( lienWei );
        }

        QLabel   * label   = newLabel("综合评价结果");
        QLineEdit* lienResult   = new QLineEdit;
        w2_layout->addWidget( label, show2Str.size()+1, 0 );
        w2_layout->addWidget( lienResult, show2Str.size()+1, 1, 1, 2 );
        editsResult.push_back(  lienResult );

        tab->addTab( widget, QString("方案%1").arg(i+1) );
    }


    QWidget * widget = new QWidget;
    QGridLayout* layout2 = new QGridLayout(widget);
    layout2->addWidget( tab );
    return widget;
}

Form_MainWidget::~Form_MainWidget()
{
}
