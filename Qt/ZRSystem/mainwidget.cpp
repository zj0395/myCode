#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QSpacerItem>
#include <fstream>
#include <QDir>
#include <iomanip>

using std::ofstream;
using std::ifstream;


# pragma execution_character_set("utf-8")//可以使用中文

int   rule0_Num = 4;
VInt  rule1_Num = {3, 2, 4, 2 };

VQStr rule2_0   = { "水文、气象状况",
                    "地形地貌情况" };
VQStr rule2_1   = { "宏观经济调控",
                    "市场需求和价格"};
VQStr rule2_2   = { "法律法规政策调整",
                    "环境保护要求",
                    "对周围道路及公用设施的保护要求" };
VQStr rule2_3   = { "平面布置合理性",
                    "项目管理团队配备及协调能力",
                    "施工队伍技术熟练程度",
                    "材料设备报验及管理情况",
                    "机械班组维护及管理情况"};
VQStr rule2_4   = { "图纸问题审查",
                    "设计变更管理",
                    "施工技术危险性",
                    "技术交底制度"};
VQStr rule2_5   = { "质量因素控制",
                    "质量管理体系",
                    "现场巡查与固定周期检查",
                    "质量通病与防治",
                    "成品保护制度"};
VQStr rule2_6   = { "关键工序控制点",
                    "资源供应计划编制合理性"
                    "工期检查与保证"};
VQStr rule2_7   = { "安全生产责任与教育",
                    "安全生产控制措施",
                    "消防安全防范管理",
                    "文明建设施工情况"};
VQStr rule2_8   = { "专项资金预留",
                    "应急团队能力",
                    "应急预案设置",
                    "应急资源配备"};
VQStr rule2_9   = { "信息获取",
                    "事件跟踪"};
VQStr rule2_10  = { "信息通报速度",
                    "应急决策能力",
                    "应急处理方案"};

VVQStr rule2    = { rule2_0, rule2_1, rule2_2,
                    rule2_3, rule2_4, rule2_5,
                    rule2_6, rule2_7, rule2_8,
                    rule2_9, rule2_10};
VQStr  rule1    = { "自然条件", "经济形势", "政策因素",
                    "施工现场管理", "项目施工技术",
                    "质量保障", "工期保障", "安全文明生产", "应急管理",
                    "监测监控", "应急处置"};
VQStr  rule0    = { "项目外环境",
                    "项目内环境",
                    "非事故状态的稳定",
                    "事故状态的应急"};


const int DegreeSize = 5;//隶属度的个数

#ifdef Q_OS_LINUX
inline void myOpenFileOut(ofstream & fs, const QString & filePath)
{
    fs.open( filePath.toStdString().c_str(), ios::out|ios::trunc );
}
inline void myOpenFileIn(ifstream & fs, QString & filePath)
{
    fs.open( filePath.toStdString().c_str(), ios::in );
}
#else
#ifdef Q_OS_WIN
inline void myOpenFileOut(ofstream & fs, const QString & filePath)
{
    fs.open( filePath.toStdWString().c_str(), std::ios::out|std::ios::trunc );
}
inline void myOpenFileIn(ifstream & fs, const QString & filePath)
{
    fs.open( filePath.toStdWString().c_str(), std::ios::in );
}
#endif
#endif


static void save1DResult( ofstream& fout, const VDouble& data )
{
    using namespace std;
    for( int i=0; i<data.size(); ++i )
    {
        fout<<setw(10)<<setprecision(7)<<data[i]<<"  ";
    }
    fout<<"\n";
}

static void saveResult( QString str, const VVDouble& layer1, const VVDouble & layer0, const VDouble & final )
{
    ofstream fout;
    myOpenFileOut( fout, str );

    fout.setf( std::ios::showbase| std::ios::left);

    fout<<"\n要素层结果:\n";
    for( int i=0; i<layer1.size(); ++i )
    {
        save1DResult( fout, layer1[i] );
    }

    fout<<"\n准则层结果:\n";
    for( int i=0; i<layer0.size(); ++i )
    {
        save1DResult( fout, layer0[i] );
    }

    fout<<"\n最终结果:\n";
    save1DResult( fout, final );

    fout.close();
}


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    this->setWindowTitle( tr("化工园区生产安全免疫力评估系统") );

    int rule2Idx = 0;
    for( int first=0; first<rule0_Num; ++first )
    {
        ui->tabWidget1->setCurrentIndex( first );
        QWidget * nowTab = ui->tabWidget1->currentWidget();
        QGridLayout * gLayout = new QGridLayout(nowTab);

        gLayout->addLayout( newLayout( 0 ), 0, 0 );

        QTabWidget * tabWidget = new QTabWidget();

        for( int second =0; second<rule1_Num[first]; ++second )
        {
            tabWidget->addTab( addLayoutToWidget( rule2[rule2Idx] ), rule1[rule2Idx] ) ;
            ++rule2Idx;
        }
        QGridLayout * gLayout2 = new QGridLayout(tabWidget);

        gLayout->addWidget( tabWidget );
    }
}

QHBoxLayout * MainWidget::newLayout(  int layer )
{
    QHBoxLayout* hLayout = new QHBoxLayout;
    QGridLayout* gLayout = new QGridLayout;
    if( layer == 0 )
    {
        addWeidht( gLayout, "单一权重", 0, layer0);
    }
    else if( layer == 1 )
    {
        addWeidht( gLayout, "单一权重", 0, layer1 );
        addWeidht( gLayout, "复合权重", 1, layer1 );
    }
    else if( layer == 2 )
    {
        addWeidht( gLayout, "单一权重",  0, layer2 );
        addWeidht( gLayout, "复合权重A", 1, layer2 );
        addWeidht( gLayout, "复合权重B", 2, layer2 );
        addWeidht( gLayout, "得分",    3, score2 );
    }
    hLayout->addLayout( gLayout );

    return hLayout;
}

void MainWidget::addWeidht(QGridLayout* gLayout, QString str, int row, VLineEdit &layer)
{
    QLabel * label = new QLabel( str );
    QLineEdit * edit = new QLineEdit;
    gLayout->addWidget( label,  row, 0 );
    gLayout->addWidget( edit,   row, 1 );

    layer.push_back( edit );
}

QWidget* MainWidget::addLayoutToWidget(  const VQStr & content)
{
    QWidget * Widget = new QTabWidget();
    QGridLayout * layout = new QGridLayout(Widget);
    layout->addLayout( newLayout(1), 0, 0 );

    QTabWidget * tabWidget = new QTabWidget;

    for( int i=0; i<content.size(); ++i )
    {
        QTabWidget * tabWidget2 = new QTabWidget();
        QGridLayout * gLayout2 = new QGridLayout(tabWidget2);
        gLayout2->addLayout( newLayout( 2 ), 0, 0 );
        tabWidget->addTab( tabWidget2, content[i]);
    }

    layout->addWidget( tabWidget );
    return Widget;
}

MainWidget::~MainWidget()
{
    delete ui;
}

#define CHECK_0( lay, str )\
{\
    if( lay->text().isEmpty() )\
    {\
        information( "提示", str );\
        return false;\
    }\
}

#define CHECK_1( lay, idx, str  )\
{\
    if( lay->text().isEmpty() )\
    {\
        QString info;\
        if( idx == 0 )\
            info = "单一权重";\
        else if(idx == 1 )\
            info = "复合权重A";\
        else if( idx == 2 )\
            info = "复合权重B";\
        information( "提示", QString("%1 %2 为空").arg(str).arg( info ) );\
        return false;\
    }\
}

bool MainWidget::checkLineEdit()
{
//    for( int i=0; i<layer0.size(); ++i )
//    {
//        CHECK_0( layer0[i], QString("%1 权重为空").arg(rule0[i]) );
//    }

//    for( int i=0; i<layer1.size(); ++i )
//    {
//        //奇数符合，偶数单一
//        CHECK_0( layer1[i],  QString("%1 %2 权重为空").arg(rule1[i/2])
//                                .arg( i%2 ? "复合" : "单一" ) );
//    }

    int allIdx = 0;
    for( int rule2Idx =0; rule2Idx<rule2.size(); ++rule2Idx )
    {
        for( int j=0; j<rule2[rule2Idx].size(); ++j )
        {
            for( int i=0; i<3; ++i )
                CHECK_1( layer2[allIdx*3+i], i, rule2[rule2Idx][j] );
            CHECK_0( score2[allIdx], QString("%1 得分为空").arg(rule2[rule2Idx][j]) );
            ++allIdx;
        }
    }
    return true;
}

void MainWidget::on_pushButton_clicked()
{
//    if( ! checkLineEdit() )
//        return;

    VVDouble degrees;//所有指标层的分数隶属度
    VDouble  oneWeights;//所有指标层的单一权重
    VDouble  comWeightA;//所有指标层的复合权重A
    VDouble  comWeightB;//所有指标层的复合权重B

    for( int i=0; i<score2.size(); ++i )
    {
        VDouble degree( DegreeSize, 0 );
        for( int j=0; j<DegreeSize; ++j )
        {
            degree[j] = getDegree( j, score2[i]->text().toDouble() );
        }
        degrees.push_back( degree );
    }

    int allIdx = 0;
    for( int rule2Idx =0; rule2Idx<rule2.size(); ++rule2Idx )
    {
        for( int j=0; j<rule2[rule2Idx].size(); ++j )
        {
            oneWeights.push_back( layer2[allIdx*3+0]->text().toDouble() );
            comWeightA.push_back( layer2[allIdx*3+1]->text().toDouble() );
            comWeightB.push_back( layer2[allIdx*3+2]->text().toDouble() );
            ++allIdx;
        }
    }


    allIdx = 0;
    //要素层计算
    VVDouble resultLayer1;
    for( int rule2Idx =0; rule2Idx<rule2.size(); ++rule2Idx )
    {
        resultLayer1.push_back( getLayerResult( oneWeights, degrees, allIdx, rule2[rule2Idx].size() ) );
        allIdx += rule2[rule2Idx].size();
    }


    allIdx = 0;
    int rule2Idx = 0;
    //准则层计算
    VVDouble resultLayer0;
    for( int rule0Idx =0; rule0Idx<rule0_Num; ++rule0Idx )
    {
        int rule1NowNum = 0;

        for( int second = 0; second<rule1_Num[rule0Idx]; ++second )
        {
            for( int third = 0; third<rule2[rule2Idx].size(); ++third )
                ++rule1NowNum;
            ++rule2Idx;
        }
        resultLayer0.push_back( getLayerResult( comWeightA, degrees, allIdx, rule1NowNum ) );
        allIdx += rule1NowNum;
    }

    //最终结果计算
    VDouble resultFinal = getLayerResult( comWeightB, degrees, 0, degrees.size() );


    QString resultPath = QDir::currentPath() + "/result.txt" ;

    saveResult( resultPath, resultLayer1, resultLayer0, resultFinal );

    information( "完成", "已保存文件\n请查看" );
}

VDouble MainWidget::getLayerResult( VDouble& oneWeigths, VVDouble & degress, int beginIdx, int num )
{
    VDouble oneResult;
    for( int j=0; j<DegreeSize; ++j )
    {
        double ret = 0;
        for( int i=0; i<num; ++i )
        {
            ret +=  oneWeigths[ beginIdx+i ] * degress[ beginIdx+i ][j];
        }
        oneResult.push_back( ret );
    }
    return oneResult;
}

double MainWidget::getDegree( int idx, double score )
{
    if( idx == 0 )
    {
        if( score < 60 )
            return 1;
        else if( score >= 60 && score<= 62.5 )
            return (250-4*score)/10;
        else
            return 0;
    }
    else if( idx == 1 )
    {
        if( score < 60 || score > 72.5)//TODO 60
            return 0;
        else if( score > 60 && score < 62.5 )
            return (4*score-240)/10;
        else if( score >= 62.5 && score <= 67.5 )
            return 1;
        else
            return (290-4*score)/20;
    }
    else if( idx == 2 )
    {
        if( score < 67.5 || score > 82.5)//TODO 67.5
            return 0;
        else if( score > 67.5 && score< 72.5 )
            return (4*score-270)/20;
        else if( score >= 72.5 && score <= 77.5 )
            return 1;
        else
            return (330-4*score)/20;
    }
    else if( idx == 3 )
    {
        if( score < 77.5 || score > 90)//TODO 77.5
            return 0;
        else if( score > 77.5 && score < 82.5 )
            return (4*score-310)/20;
        else if( score >= 82.5 && score <= 87.5 )
            return 1;
        else
            return (360-4*score)/10;
    }
//    else if( idx == 4 )
    else
    {
        if( score < 87.5)
            return 0;
        else if( score >= 87.5 && score <= 90 )
            return (4*score-350)/10;
        else
            return 1;
    }
}

void MainWidget::information( QString title, QString content )
{
    QMessageBox::information( this, title, content );
}
