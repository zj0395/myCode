#include "widget.h"
#include "ui_widget.h"
#include "ogrsf_frmts.h"
#include <QFileInfo>
#include <QPointF>
#include <QPolygonF>
#include <fstream>
#include <QMessageBox>
#include <QDebug>

typedef std::vector<double> VDouble;

#define MES_INFORMATION( title, content )\
{\
    QMessageBox::information( this, title, content );\
}
#define CHECK_WRONG_MES( str )\
{\
    if( ! str.isEmpty() )\
    {\
        MES_INFORMATION( tr("错误"), str );\
        return;\
    }\
}
#define CHECK_OPEN_FILE( filePath )\
{\
    if( filePath.isEmpty() )\
    {\
        MES_INFORMATION( tr("提示"), tr("未选择影像") );\
        return;\
    }\
    if( ! QFileInfo(filePath).exists() )\
    {\
        MES_INFORMATION( tr("提示"), tr("文件 %1 不存在").arg(filePath) );\
        return;\
    }\
}
inline void STR_NoSpace(QString & str)
{
    str = str.simplified();
    str.remove(' ');
}
VDouble readTxtDouble(const char *txtFile)
{
    typedef std::istream_iterator<double> iterDouble;
    std::ifstream fin( txtFile );
    if( !fin )
    {
        return VDouble();//返回空数组
    }

    //读取整个文件的 double 数据
    //第一个参数是指向文件开头位置的迭代器；第二个参数为指向空数据的迭代器，代表文件结尾
    VDouble fileData( (iterDouble(fin)), iterDouble() );

//    DEBUG<<fileData.size();
//    for_each( fileData.begin(), fileData.end(), [](double tmp){DEBUG<<tmp;});

    return fileData;
}
QString transform( QPolygonF& points, const OGRSpatialReference & fromOGRS,
                   const OGRSpatialReference & destOGRS )
{
    if(  fromOGRS.IsSame(&destOGRS) )
        return "二者相同";

    OGRSpatialReference from ( fromOGRS );
    OGRSpatialReference dest ( destOGRS );
    OGRCoordinateTransformation * ct = OGRCreateCoordinateTransformation( &from, &dest );
    if( ! ct )
        return "不支持该坐标系间的转换";

    const int pointCount = points.size();
    VDouble xVector(pointCount, 0);
    VDouble yVector(pointCount, 0);

    //坐标保存为x的数组和y的数组，以适应transform的接口
    for( int j=0; j<pointCount; ++j )
    {
        xVector[j] = points[j].x();
        yVector[j] = points[j].y();
    }

    ct->Transform( pointCount, &xVector[0], &yVector[0] );

    //转换完毕，赋值回来
    for( int j=0; j<pointCount; ++j )
    {
        points[j].setX( xVector[j] );
        points[j].setY( yVector[j] );
    }

    return "";
}

OGRSpatialReference * buildOgr();
const OGRSpatialReference& getOGR( int i )
{
    static const OGRSpatialReference * orgSpa = buildOgr();
    char*s;
    orgSpa[i].exportToWkt(&s);
    qDebug()<<s;
    return orgSpa[i];
}

//需要手动保证这 bulidOgr 的顺序和 GEOS 的顺序相同
const QStringList Widget::GEOS = {"WGS84", "CGCS2000", "1954北京坐标系"};
OGRSpatialReference * buildOgr()
{
    int count = Widget::GEOS.size();
    OGRSpatialReference * orgSpa = new OGRSpatialReference[count];
    orgSpa[0].SetWellKnownGeogCS( "WGS84" );

    char* cgcs2000 = "GEOCCS[\"China Geodetic Coordinate System 2000\",DATUM[\"China_2000\",SPHEROID[\"CGCS2000\",6378137,298.257222101,AUTHORITY[\"EPSG\",\"1024\"]],AUTHORITY[\"EPSG\",\"1043\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"metre\",1,AUTHORITY[\"EPSG\",\"9001\"]],AXIS[\"Geocentric X\",OTHER],AXIS[\"Geocentric Y\",OTHER],AXIS[\"Geocentric Z\",NORTH],AUTHORITY[\"EPSG\",\"4479\"]]";
    orgSpa[1].importFromWkt( &cgcs2000 );
    orgSpa[2].SetWellKnownGeogCS( "WGS84" );
    return orgSpa;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    buildCombox();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buildCombox()
{
    ui->fromGeos->addItems( GEOS );
    ui->destGeos->addItems( GEOS );
}

void Widget::on_fileOption_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex( index );
}

void Widget::on_buttonTransform_clicked()
{
    int fromPro = getFromPro();
    int destPro = getDestPro();
    if( ui->stackedWidget->currentWidget() == ui->oneTransform )
    {
        onePointTransform( fromPro, destPro );
    }
    else
    {
        fileTransfrom( fromPro, destPro );
    }
}

int Widget::getFromPro()
{
    return ui->fromGeos->currentIndex();
}

int Widget::getDestPro()
{
    return ui->destGeos->currentIndex();
}

void Widget::onePointTransform( int fromPro, int destPro )
{
    QString fromPointStr = ui->lineEditBegin->text();
    STR_NoSpace( fromPointStr );

    if( fromPointStr.isEmpty() )
    {
        MES_INFORMATION( tr("提示"), tr("无输入") );
        return;
    }

    int index = fromPointStr.indexOf(',');

    if( index == -1 )
    {
        MES_INFORMATION( tr("提示"), tr("坐标输入不规范\n"
                                      "x,y,z 用英文逗号隔开") );
        return;
    }

    QString xLoc = fromPointStr.left( index );
    QString yLoc = fromPointStr.mid(  index+1 );

    QPolygonF poly;
    poly.push_back( QPointF( xLoc.toDouble(), yLoc.toDouble() ) );

    QString ret = transform( poly, getOGR(fromPro), getOGR(destPro) );
    CHECK_WRONG_MES( ret );

    QString str = QString::number(poly[0].x()) + ", " + QString::number(poly[0].x());
    ui->lineEditAfter->setText( str );
}

void Widget::fileTransfrom(int fromPro, int destPro )
{

}
