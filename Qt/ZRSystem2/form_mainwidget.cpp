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

//综合评价结果未参与运算，所以不和这些参与运算的一些处理
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


#define MSG_INFORMATION( str )\
{\
    QMessageBox::information( this, tr("错误"), str+" 输入为空" );\
}

//检查 风险事件 中的输入
#define CHECK_LINEEDIT_FIRST( lineedit, str )\
{\
    if( lineedit->text().isEmpty() )\
    {\
        mainWidget.setCurrentIndex( 0 );\
        MSG_INFORMATION(str);\
        return false;\
    }\
}

//检查 方案 中的输入
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

//移动窗口，更改显示位置
extern void moveWidget( QWidget * widget, QPoint pos );

QLabel* newLabel(QString str)
{
    QLabel * label = new QLabel(str);
    //居中显示
    label->setAlignment( Qt::AlignCenter );
    return label;
}

QTableWidgetItem* newTableItem( QString str )
{
    QTableWidgetItem * item = new QTableWidgetItem( str );
    //居中显示
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

QLineEdit* newLineEdit()
{
    QLineEdit* lienWei = new QLineEdit;

    QSizePolicy policy = lienWei->sizePolicy();
    policy.setVerticalPolicy(  QSizePolicy::Expanding );
    lienWei->setSizePolicy( policy );

    return lienWei;
}

/**
 * @brief getOneResult  进行计算
 * @param risks         方案里输入的风险量
 * @param weights       方案里的权重
 * @param wholeRisk     全局的设置，即风险事件里的设置
 * @return
 */
double getOneResult( const VDouble& risks, const VDouble& weights, const VDouble & wholeRisk )
{
    //以下均为提供的公式
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

    //getFirstWidget 是风险事件的窗口
    mainWidget.addTab(  getFirstWidget(), "风险事件");
    //getPlanWidget  是方案的窗口
    mainWidget.addTab(  getPlanWidget(),  "预防方案");


    //添加一个 单选框 和 一个 开始计算 的按钮
    QHBoxLayout * vlayout  = new QHBoxLayout;
    QRadioButton* ratioBut = new QRadioButton("空行视为0");
    QPushButton * buttonDo = new QPushButton("开始计算");
    vlayout->addStretch();
    vlayout->addWidget(ratioBut);
    vlayout->addWidget(buttonDo);

    //点击了是否 空行视为0
    connect( ratioBut, &QPushButton::clicked,
             [=](bool sta)
    {
        b_checkEmptyLine = !sta;
    });
    //点击了 开始计算
    connect( buttonDo, &QPushButton::clicked,
             [=]()
    {
        doCalculate();
    });


    //窗口显示位置
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget( &mainWidget, 0, 0 );
    layout->addLayout( vlayout, 1, 0 );

    //窗口大小
    resize( 500, 250 );

    //默认 空行 不 视为0
    b_checkEmptyLine = true;
}


//风险事件的窗口
QWidget* Form_MainWidget::getFirstWidget()
{
    QWidget * widget = new QWidget;
    QGridLayout * layout = new QGridLayout( widget );

    for( int j=0; j<show1Str.size(); ++j )
    {
        QLabel   * label   = newLabel(show1Str[j]);
        QLineEdit* lienA   = newLineEdit();

        layout->addWidget( label, j, 0 );
        layout->addWidget( lienA, j, 1 );

        edits[0].push_back(   lienA );
    }

    //不保存这个 lineedit
    QLabel   * label   = newLabel("综合评价结果");
    QLineEdit* lienResult   = newLineEdit();
    layout->addWidget( label,      show1Str.size()+1, 0 );
    layout->addWidget( lienResult, show1Str.size()+1, 1 );

    return widget;
}

//检查各个输入框是否为空
bool Form_MainWidget::checkEmpty()
{
    //先检查 总设置，即风险设置
    for( int i=0; i<edits[0].size(); ++i )
    {
        CHECK_LINEEDIT_FIRST(edits[0][i], show1Str[i] );
    }

    //再检查每个方案的 风险量和权重
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

    //检查每个方案 最终评价结果的输入
    for( int i=0; i<editsResult.size(); ++i )
    {
        CHECK_LINEEDIT_PLAN( editsResult[i], "最终评价结果", i );
    }

    return true;
}

void Form_MainWidget::doCalculate()
{
    //是否检查空行
    if( b_checkEmptyLine )
    {
        //如果检查空行，结果是 false，就返回，不进行计算
        if( ! checkEmpty() )
            return;
    }


    //通过了检查，现在开始计算


    //风险事件的输入，即 A-D
    VDouble wholeRisk;
    for( int i=0; i<edits[0].size(); ++i )
    {
        wholeRisk.push_back( edits[0][i]->text().toDouble() );
    }

    //保存三个方案的计算的结果
    VDouble result;

    //有三个方案
    for( int planIdx=0; planIdx<PLAN_NUMBER; ++planIdx )
    {
        //两个数组，风险量和权重，A1-D1与P1-P3，第一个数组是风险量，第二个数组是权重
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

        //计算该方案的最后结果
        double onePlanResult  = getOneResult( risksAndWeights[0], risksAndWeights[1], wholeRisk  );

        result.push_back( onePlanResult );
    }

    //输入的三个综合评价结果
    VQString inputResult;
    for( int i=0; i<editsResult.size(); ++i )
    {
        inputResult.push_back( editsResult[i]->text() );
    }


    //显示结果
    showResult( result, inputResult );
}

void Form_MainWidget::showResult( const VDouble & result, const VQString & inputResult )
{
    ShowWidget* showWidget = new ShowWidget(result, inputResult);
    moveWidget( showWidget, this->pos()-QPoint(40, -40) );
    showWidget->show();
}

//获取 预防方案的窗口
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
            QLabel   * label   = newLabel(show2Str[j]);//显示的标签
            QLineEdit* lienA   = newLineEdit();//风险量的输入框

            w2_layout->addWidget( label,   j+1, 0 );
            w2_layout->addWidget( lienA,   j+1, 1 );

            int rowSpan = 1;
            if( j != 1 )//因为第一行与第二行共用一个 权重，所以第二行没有权重的输入框
            {
                QLineEdit* lienWei = newLineEdit();//权重的输入框

                if( j == 0 )
                {
                    rowSpan = 2;//因为第一行与第二行共用一个 权重，所以第一个权重占用两行，其它的都是一行
                }

                w2_layout->addWidget( lienWei, j+1, 2, rowSpan, 1 );
                edits[i*2+2].push_back( lienWei );
            }

            edits[i*2+1].push_back(   lienA );
        }

        QLabel   * label   = newLabel("综合评价结果");
        QLineEdit* lienResult   = newLineEdit();

        //综合评价结果和它的输入框 放到最后一行
        w2_layout->addWidget( label, show2Str.size()+1, 0 );
        //占用两列
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


//显示结果的窗口
ShowWidget::ShowWidget(const VDouble &result, const VQString &inputResult) : myId( allID++ )
{
    this->setRowCount( 3 );
    this->setColumnCount( 2 );

    this->setWindowTitle( QString("评价结果%1").arg(myId) );

    QStringList titles;
    titles<<"评价结果"<<"综合评价结果";
    this->setHorizontalHeaderLabels( titles );

    QStringList headrs;
    headrs<<"方案1"<<"方案2"<<"方案3";
    this->setVerticalHeaderLabels( headrs );

    this->setEditTriggers( QAbstractItemView::NoEditTriggers );
    this->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    this->verticalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    for( int i=0; i<result.size(); ++i )
    {
        this->setItem( i, 0, newTableItem( QString::number( result[i] ) ) );
        this->setItem( i, 1, newTableItem( inputResult[i] ) );
    }

    this->setMinimumSize( 300, 120 );
    resize( 500, 150 );
}

ShowWidget::~ShowWidget()
{

}

void ShowWidget::closeEvent(QCloseEvent *event)
{
    delete this;
}
