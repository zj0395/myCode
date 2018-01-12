#include "form_mainwidget.h"
#include <QGridLayout>
#include <QStandardItem>
#include <QLabel>
#include <QDebug>
#include <QRadioButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include <cmath>

# pragma execution_character_set("utf-8")//可以使用中文

int ShowWidget::allID = 1;

const VQString show1Str = { "损失成本",
                            "发生概率",
                            "工期影响",
                            "质量影响"
                          };

const VQString show2Str = { "预防成本",
                            "发生概率",
                            "工期影响",
                            "质量影响"
                          };

QLabel* newLabel(QString str)
{
    QLabel * label = new QLabel(str);
    label->setAlignment( Qt::AlignCenter );
    return label;
}

QLineEdit* newLineEdit()
{
    QLineEdit* lienWei = new QLineEdit;

    QSizePolicy policy = lienWei->sizePolicy();
    policy.setVerticalPolicy(  QSizePolicy::Expanding );
    lienWei->setSizePolicy( policy );

    return lienWei;
}

double getOneResult( const VDouble& risks, const VDouble& weights, const VDouble & wholeRisk )
{
    double tmp0 =  risks[0]*risks[1] - wholeRisk[0] * wholeRisk[1];
    tmp0 = std::pow( tmp0, 2 ) * weights[0];

    double tmp1 = std::pow( risks[2]-wholeRisk[2], 2 ) * weights[1];
    double tmp2 = std::pow( risks[3]-wholeRisk[3], 2 ) * weights[2];

    return std::sqrt( tmp0 + tmp1 + tmp2 );
}


Form_MainWidget::Form_MainWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle( "工程风险预防方案选择系统" );

    mainWidget.addTab(  getFirstWidget(), "总设置");
    mainWidget.addTab(  getPlanWidget(),  "方案选择");


    QHBoxLayout * vlayout  = new QHBoxLayout;
    QRadioButton* ratioBut = new QRadioButton("空行视为0");
    QPushButton * buttonDo = new QPushButton("开始计算");
    vlayout->addStretch();
    vlayout->addWidget(ratioBut);
    vlayout->addWidget(buttonDo);

    connect( ratioBut, &QPushButton::clicked,
             [=](bool sta)
    {
        b_checkEmptyLine = !sta;
    });
    connect( buttonDo, &QPushButton::clicked,
             [=]()
    {
        doCalculate();
    });


    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget( &mainWidget, 0, 0 );
    layout->addLayout( vlayout, 1, 0 );

    resize( 500, 250 );

    b_checkEmptyLine = true;
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
        QLineEdit* lienA   = newLineEdit();

        layout->addWidget( label, j+1, 0 );
        layout->addWidget( lienA, j+1, 1 );

        edits[0].push_back(   lienA );
    }

    //不保存这个 lineedit
    QLabel   * label   = newLabel("综合评价结果");
    QLineEdit* lienResult   = newLineEdit();
    layout->addWidget( label,      show1Str.size()+1, 0 );
    layout->addWidget( lienResult, show1Str.size()+1, 1 );

    return widget;
}

#define MSG_INFORMATION( str )\
{\
    QMessageBox::information( this, tr("错误"), str+" 输入为空" );\
}

#define CHECK_LINEEDIT_FIRST( lineedit, str )\
{\
    if( lineedit->text().isEmpty() )\
    {\
        mainWidget.setCurrentIndex( 0 );\
        MSG_INFORMATION(str);\
        return false;\
    }\
}

#define CHECK_LINEEDIT_PLAN( lineedit, str, idx )\
{\
    if( lineedit->text().isEmpty() )\
    {\
        mainWidget.setCurrentIndex( 1 );\
        planTab.setCurrentIndex( idx );\
        MSG_INFORMATION(QString("方案%1: ").arg(idx+1)+str);\
        return false;\
    }\
}

bool Form_MainWidget::checkEmpty()
{
    for( int i=0; i<edits[0].size(); ++i )
    {
        CHECK_LINEEDIT_FIRST(edits[0][i], show1Str[i] );
    }

    for( int planIdx=0; planIdx<PLAN_NUMBER; ++planIdx )
    {
        //风险量和权重
        for( int i=0; i<2; ++i )
        {
            VQLineEdit & lines = edits[ 1 + planIdx*2 + i ];
            for( int j=0; j<lines.size(); ++j )
            {
                CHECK_LINEEDIT_PLAN( lines[j], show2Str[j], planIdx );
            }
        }
    }

    for( int i=0; i<editsResult.size(); ++i )
    {
        CHECK_LINEEDIT_PLAN( editsResult[i], "最终评价结果", i );
    }

    return true;
}

void Form_MainWidget::doCalculate()
{
    if( b_checkEmptyLine )
    {
        if( ! checkEmpty() )
            return;
    }

    //全局设置 A-D
    VDouble wholeRisk;
    for( int i=0; i<edits[0].size(); ++i )
    {
        wholeRisk.push_back( edits[0][i]->text().toDouble() );
    }

    //三个方案的结果
    VDouble result;

    //有三个方案
    for( int planIdx=0; planIdx<PLAN_NUMBER; ++planIdx )
    {
        //风险量和权重，A1-D1与P1-P4
        VDouble risksAndWeights[2];

        //风险量和权重
        for( int i=0; i<2; ++i )
        {
            VQLineEdit & lines = edits[ 1 + planIdx*2 + i ];
            for( int j=0; j<lines.size(); ++j )
            {
                risksAndWeights[i].push_back( lines[j]->text().toDouble() );
            }
        }

        VDouble risks   = risksAndWeights[0];
        VDouble weights = risksAndWeights[1];

        result.push_back( getOneResult( risks, weights, wholeRisk  ) );
    }

    //输入的三个评价结果
    VDouble inputResult;
    for( int i=0; i<editsResult.size(); ++i )
    {
        inputResult.push_back( editsResult[i]->text().toDouble() );
    }


    showResult( result, inputResult );
}

void Form_MainWidget::showResult( const VDouble & result, const VDouble & inputResult )
{
    ShowWidget* showWidget = new ShowWidget(result, inputResult);
    showWidget->show();
}

QWidget* Form_MainWidget::getPlanWidget()
{
    for( int i=0; i<PLAN_NUMBER; ++i )
    {
        QWidget * widget = new QWidget;
        QGridLayout * w2_layout = new QGridLayout( widget );

        QLabel * label1 = newLabel("风险量");
        QLabel * label2 = newLabel("权重");
        label1->setMaximumHeight( 30 );
        w2_layout->addWidget( label1, 0, 1, 1, 1 );
        w2_layout->addWidget( label2, 0, 2, 1, 1 );

        for( int j=0; j<show2Str.size(); ++j )
        {
            QLabel   * label   = newLabel(show2Str[j]);
            QLineEdit* lienA   = newLineEdit();

            w2_layout->addWidget( label,   j+1, 0 );
            w2_layout->addWidget( lienA,   j+1, 1 );

            int rowSpan = 1;
            if( j != 1 )
            {
                QLineEdit* lienWei = newLineEdit();

                if( j == 0 )
                {
                    rowSpan = 2;
                }

                w2_layout->addWidget( lienWei, j+1, 2, rowSpan, 1 );
                edits[i*2+2].push_back( lienWei );
            }

            edits[i*2+1].push_back(   lienA );
        }

        QLabel   * label   = newLabel("综合评价结果");
        QLineEdit* lienResult   = newLineEdit();
        w2_layout->addWidget( label, show2Str.size()+1, 0 );
        w2_layout->addWidget( lienResult, show2Str.size()+1, 1, 1, 2 );
        editsResult.push_back(  lienResult );

        planTab.addTab( widget, QString("方案%1").arg(i+1) );
    }


    QWidget * widget = new QWidget;
    QGridLayout* layout2 = new QGridLayout(widget);
    layout2->addWidget( &planTab );
    return widget;
}

Form_MainWidget::~Form_MainWidget()
{
}

QTableWidgetItem* newTableItem( double num )
{
    QTableWidgetItem * item = new QTableWidgetItem( QString::number( num ) );
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

ShowWidget::ShowWidget(const VDouble &result, const VDouble &inputResult) : myId( allID++ )
{
    this->setRowCount( 3 );
    this->setColumnCount( 2 );

    this->setWindowTitle( QString("评价结果%1").arg(myId) );

    QStringList titles;
    titles<<"综合评价结果"<<"评价结果";
    this->setHorizontalHeaderLabels( titles );

    QStringList headrs;
    headrs<<"方案1"<<"方案2"<<"方案3";
    this->setVerticalHeaderLabels( headrs );

    this->setEditTriggers( QAbstractItemView::NoEditTriggers );
    this->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    this->verticalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    for( int i=0; i<result.size(); ++i )
    {
        this->setItem( i, 0, newTableItem( result[i]      ) );
        this->setItem( i, 1, newTableItem( inputResult[i] ) );
    }
}

ShowWidget::~ShowWidget()
{

}

void ShowWidget::closeEvent(QCloseEvent *event)
{
    delete this;
}
