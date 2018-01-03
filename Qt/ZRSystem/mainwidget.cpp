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
#include <QSettings>
#include "showform.h"

# pragma execution_character_set("utf-8")//可以使用中文

using std::ofstream;
using std::ifstream;


#define CHECK_LAYER0( lay, str )\
{\
    if( lay->text().isEmpty() )\
    {\
        information( "提示", str );\
        return false;\
    }\
}

#define CHECK_LAYER1( lay, idx, str  )\
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


int   rule0_Num = 4;

extern const
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
                    "资源供应计划编制合理性",
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
extern const
VQStr  rule1    = { "自然条件", "经济形势", "政策因素",
                    "施工现场管理", "项目施工技术", "质量保障",
                    "工期保障", "安全文明生产", "应急管理",
                    "监测监控", "应急处置"};
extern const
VQStr  rule0    = { "项目外环境",
                    "项目内环境",
                    "非事故状态的稳定",
                    "事故状态的应急"};


extern const int DegreeSize;//隶属度的个数
extern QString getIdx( int layer1Idx );

#ifdef __GNUC__
inline void myOpenFileOut(ofstream & fs, const QString & filePath)
{
    fs.open( filePath.toStdString().c_str(), std::ios::out|std::ios::trunc );
}
inline void myOpenFileIn(ifstream & fs, QString & filePath)
{
    fs.open( filePath.toStdString().c_str(), std::ios::in );
}
#else
#ifdef _MSC_VER
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


/**
 * @brief save1DResult  单个数组保存到文件
 * @param fout          文件的表示符
 * @param data          数组
 */
static void save1DResult( ofstream& fout, const VDouble& data )
{
    using namespace std;
    for( int i=0; i<data.size(); ++i )
    {
        fout<<setw(10)<<setprecision(7)<<data[i]<<"  ";
    }
    fout<<"\n";
}

/**
 * @brief MainWidget::saveResult    所有结果保存成文件
 * @param str                       文件的名字
 * @param layer1                    第二层的计算结果
 * @param layer0                    第一层的计算结果
 * @param final                     最终结果
 */
void MainWidget::saveResult( QString str, const VVDouble& layer1, const VVDouble & layer0, const VDouble & final )
{
    ofstream fout;
    myOpenFileOut( fout, str );

    fout.setf( std::ios::showbase| std::ios::left);

    fout<<"要素层结果:\n";
    for( int i=0; i<layer1.size(); ++i )
    {
        save1DResult( fout, layer1[i] );
    }

    fout<<"\n准则层结果:\n";
    for( int i=0; i<layer0.size(); ++i )
    {
        save1DResult( fout, layer0[i] );
    }

    fout<<"\n目标层结果:\n";
    save1DResult( fout, final );

    fout.close();
}


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    this->setWindowTitle( tr("工程项目风险识别系统") );

    int rule2Idx = 0;
    for( int first=0; first<rule0_Num; ++first )
    {
        //第一层的选项卡窗口
        ui->tabWidget1->setCurrentIndex( first );
        QWidget * nowTab = ui->tabWidget1->currentWidget();
        QGridLayout * gLayout = new QGridLayout(nowTab);

        gLayout->addLayout( newLayout( 0 ), 0, 0 );

        //第二层的选项卡窗口
        QTabWidget * tabWidget = new QTabWidget();

        for( int second =0; second<rule1_Num[first]; ++second )
        {
            //第三层的选项卡窗口
            tabWidget->addTab( newChildWidget( rule2[rule2Idx] ), rule1[rule2Idx] ) ;
            ++rule2Idx;
        }
        QGridLayout * gLayout2 = new QGridLayout(tabWidget);

        gLayout->addWidget( tabWidget );
    }

    readIniFile();

    ui->tabWidget1->setCurrentIndex( 0 );
}

/**
 * @brief MainWidget::newLayout
 * @param layer                 层号, 取值 0-2
 * @return                      返回一个水平布局
 */
QHBoxLayout * MainWidget::newLayout(  int layer )
{
    QHBoxLayout* hLayout = new QHBoxLayout;
    QGridLayout* gLayout = new QGridLayout;
    if( layer == 0 )//第一层
    {
        addWeidht( gLayout, "权重", 0, layer0);
    }
    else if( layer == 1 )//第二层
    {
        addWeidht( gLayout, "单一权重", 0, layer1 );
        addWeidht( gLayout, "复合权重", 1, layer1 );
    }
    else if( layer == 2 )//第三层
    {
        addWeidht( gLayout, "单一权重",  0, layer2 );
        addWeidht( gLayout, "复合权重A", 1, layer2 );
        addWeidht( gLayout, "复合权重B", 2, layer2 );
        addWeidht( gLayout, "得分",     3, score2 );
    }
    hLayout->addLayout( gLayout );

    return hLayout;
}

/**
 * @brief MainWidget::addWeidht 生成输入框
 * @param gLayout               父窗口的布局
 * @param str                   权重或者得分
 * @param row                   位于布局的第几行
 * @param layer                 把输入框放置到该数组
 */
void MainWidget::addWeidht(QGridLayout* gLayout, QString str, int row, VLineEdit &layer)
{
    QLabel * label = new QLabel( str );
    QLineEdit * edit = new QLineEdit;
    gLayout->addWidget( label,  row, 0 );
    gLayout->addWidget( edit,   row, 1 );

    layer.push_back( edit );
}

/**
 * @brief MainWidget::newChildWidget    第三层的选项卡窗口
 * @param content                       单个要素层下的所有指标
 * @return                              返回值是该层所有指标组成的窗口
 */
QWidget* MainWidget::newChildWidget(  const VQStr & content)
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

//检查输入框是否为空
//前两层没有用到，所以注释掉了检查的代码
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
            QString end = QString("%1%2-%3").arg(rule2[rule2Idx][j] ).arg( getIdx(rule2Idx) ).arg(j+1);
            for( int i=0; i<3; ++i )
                CHECK_LAYER1( layer2[allIdx*3+i], i, end);
            CHECK_LAYER0( score2[allIdx], QString("%1 得分为空").arg(end) );
            ++allIdx;
        }
    }
    return true;
}

void MainWidget::on_pushButton_clicked()
{
//    testGetDegree();

    //未选择 空白视为0 则进行检查
    //检查结果为 false, 说明有错误, 就返回
    if( ! ui->radioButton->isChecked() )
        if( ! checkLineEdit() )
            return;

    //下4个数组均按顺序排列
    VVDouble degrees;//所有指标层的分数隶属度, 二维
    VDouble  oneWeights;//所有指标层的单一权重, 一维
    VDouble  comWeightA;//所有指标层的复合权重A, 一维
    VDouble  comWeightB;//所有指标层的复合权重B, 一维

    //从输入框中获取所有得分
    for( int i=0; i<score2.size(); ++i )
    {
        VDouble degree( DegreeSize, 0 );
        for( int j=0; j<DegreeSize; ++j )
        {
            degree[j] = getDegree( j, score2[i]->text().toDouble() );
        }
        degrees.push_back( degree );
    }

    //从输入框中获取所有权重
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


    //保存到文件
    QString resultPath = QDir::currentPath() + "/result.txt" ;
    saveResult( resultPath, resultLayer1, resultLayer0, resultFinal );

    //显示到窗口
    showResult( resultLayer1, resultLayer0, resultFinal );

//    information( "完成", "已保存文件到当前文件夹\n请查看" );
}


void MainWidget::showResult(const VVDouble &layer1, const VVDouble &layer0, const VDouble &final)
{
    //ShowForm 是用来显示的窗口
    ShowForm * form = new ShowForm;

    //把结果传过去
    form->setModelData( this->pos(), layer1, layer0, final );
}


/**
 * @brief getLayerResult 进行矩阵相乘
 * @param oneWeigths     权重的数组
 * @param degress        所有隶属度数组
 * @param beginIdx       两个数组的索引
 * @param num            从索引开始，使用的个数
 * @return               返回值是数组相乘所得矩阵, 大小固定 1*5
 */
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

//测试函数，不用管
void MainWidget::testGetDegree()
{
    double score = 67.5;
    for( int i=0; i<DegreeSize; ++i )
        qDebug()<<getDegree( i, score );
}

//读取 ini 配置文件，未使用，不用管
void MainWidget::readIniFile()
{
    QString iniPath = QDir::currentPath() + "/config.ini" ;
    if( !QFileInfo(iniPath).exists() )
        return;

    QSettings  iniReader ( iniPath, QSettings::IniFormat);

    qDebug()<<iniReader.value( "/气象状况/单一权重" ).toString();
    const QString weightStr[3] = {"/单一权重", "/复合权重A", "/复合权重B"};
    const QString scoreStr     = "得分";
    int allIdx = 0;
    for( int rule2Idx =0; rule2Idx<rule2.size(); ++rule2Idx )
    {
        for( int j=0; j<rule2[rule2Idx].size(); ++j )
        {
            for( int i=0; i<3; ++i )
            {
                QString iniStr = "/" + rule2[rule2Idx][j] + weightStr[i];
                layer2[allIdx*3+i]->setText( iniReader.value(iniStr).toString() );
            }
            QString iniStr = "/" + rule2[rule2Idx][j] + scoreStr;
            score2[allIdx]->setText( iniReader.value(iniStr).toString() );
            ++allIdx;
        }
    }
}

/**
 * @brief MainWidget::getDegree
 * @param idx                   序号, 取值 0-4
 * @param score                 得分
 * @return                      返回值为隶属度
 */
double MainWidget::getDegree( int idx, double score )
{
    if( idx == 0 )
    {
        if( score < 60 )
            return 1;
        else if( score >= 60 && score<= 62.5 )
            return (250-4*score)/10;
        else if( score > 62.5 )
            return 0;
        else
            return 0;
    }
    else if( idx == 1 )
    {
        if( score < 60 || score > 72.5)
            return 0;
        else if( score > 60 && score < 62.5 )
            return (4*score-240)/10;
        else if( score >= 62.5 && score <= 67.5 )
            return 1;
        else if( score > 67.5 && score < 72.5 )
            return (290-4*score)/20;
        else
            return 0;
    }
    else if( idx == 2 )
    {
        if( score < 67.5 || score > 82.5)
            return 0;
        else if( score > 67.5 && score< 72.5 )
            return (4*score-270)/20;
        else if( score >= 72.5 && score <= 77.5 )
            return 1;
        else if( score > 77.5 && score < 82.5 )
            return (330-4*score)/20;
        else
            return 0;
    }
    else if( idx == 3 )
    {
        if( score < 77.5 || score > 90)
            return 0;
        else if( score > 77.5 && score < 82.5 )
            return (4*score-310)/20;
        else if( score >= 82.5 && score <= 87.5 )
            return 1;
        else if( score > 87.5 && score < 90 )
            return (360-4*score)/10;
        else
            return 0;
    }
//    else if( idx == 4 )
    else
    {
        if( score < 87.5)
            return 0;
        else if( score >= 87.5 && score <= 90 )
            return (4*score-350)/10;
        else if( score > 90 )
            return 1;
        else
            return 0;
    }
}

//提示对话框
void MainWidget::information( QString title, QString content )
{
    QMessageBox::information( this, title, content );
}
