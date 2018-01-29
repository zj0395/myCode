#include "widget.h"
#include "ui_widget.h"
#include "ogrsf_frmts.h"
#include <QFileInfo>
#include <QPointF>
#include <QPolygonF>
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

typedef std::vector<double> VDouble;


#ifdef linux
#define CHANGE_LINE "\n"
#else
#ifdef WIN32
#define CHANGE_LINE "\r\n"
#endif
#endif


OGRSpatialReference * buildOgr();
const OGRSpatialReference& getOGR( int i );

#define BUTTON_CLICKED_OPEN_FILE( lienEdit )\
{\
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择影像"), "", "" );\
    if( !fileName.isEmpty() )\
        lienEdit->setText( fileName );\
}
#define BUTTON_CLICKED_SAVE_TXT( lienEdit )\
{\
    QString fileName = QFileDialog::getSaveFileName(this, tr("结果另存为"), "default.txt", "*.txt" );\
    if( !fileName.isEmpty() )\
        lienEdit->setText( fileName );\
}
#define CHECK_SAVE_PATH( resultPath )\
{\
    if( resultPath.isEmpty() )\
    {\
        MES_INFORMATION( tr("提示"), tr("未设置保存位置") );\
        return;\
    }\
}
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

    double zTest = 0;
    if( fromOGRS.IsSame( &getOGR( 1 ) ) )
        zTest = 4679497.745873962;
    ct->Transform( pointCount, &xVector[0], &yVector[0], &zTest );

    //转换完毕，赋值回来
    for( int j=0; j<pointCount; ++j )
    {
        points[j].setX( xVector[j] );
        points[j].setY( yVector[j] );
    }
    qDebug()<<xVector[0]<<yVector[0]<<zTest;

    return "";
}

const OGRSpatialReference& getOGR( int i )
{
    static const OGRSpatialReference * orgSpa = buildOgr();
    char*s;
    orgSpa[i].exportToWkt(&s);
    qDebug()<<s;
    return orgSpa[i];
}

//https://epsg.io/4479
//需要手动保证 bulidOgr 的顺序和 GEOS 的顺序相同
const QStringList Widget::GEOS = {"WGS84", "CGCS2000"};
OGRSpatialReference * buildOgr()
{
    int count = Widget::GEOS.size();
    OGRSpatialReference * orgSpa = new OGRSpatialReference[count];
    orgSpa[0].SetWellKnownGeogCS( "WGS84" );

    char* cgcs2000 = "GEOCCS[\"China Geodetic Coordinate System 2000\",DATUM[\"China_2000\",SPHEROID[\"CGCS2000\",6378137,298.257222101,AUTHORITY[\"EPSG\",\"1024\"]],AUTHORITY[\"EPSG\",\"1043\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"metre\",1,AUTHORITY[\"EPSG\",\"9001\"]],AXIS[\"Geocentric X\",OTHER],AXIS[\"Geocentric Y\",OTHER],AXIS[\"Geocentric Z\",NORTH],AUTHORITY[\"EPSG\",\"4479\"]]";
    orgSpa[1].importFromWkt( &cgcs2000 );
    return orgSpa;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    buildCombox();

    QPolygonF ff;
    ff.push_back( QPointF( 69.4439547, 47.5 ) );
    transform( ff, getOGR(0), getOGR(1) );
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

bool getPointFromStr( QPolygonF& poly, QString fromPointStr )
{
    int index = fromPointStr.indexOf(',');

    if( index == -1 )
    {
        return false;
    }

    QString xLoc = fromPointStr.left( index );
    QString yLoc = fromPointStr.mid(  index+1 );

    poly.push_back( QPointF( xLoc.toDouble(), yLoc.toDouble() ) );

    return true;
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

    QPolygonF poly;
    bool ret = getPointFromStr( poly, fromPointStr );
    if( ! ret  )
    {
        MES_INFORMATION( tr("提示"), tr("坐标输入不规范\n"
                                      "x,y,z 用英文逗号隔开") );
        return;
    }

    QString wrongInfo = transform( poly, getOGR(fromPro), getOGR(destPro) );
    CHECK_WRONG_MES( wrongInfo );

    QString str = QString::number(poly[0].x(), 'f', 10) + ", " + QString::number(poly[0].y(), 'f', 10);
    ui->lineEditAfter->setText( str );
}

void Widget::fileTransfrom(int fromPro, int destPro )
{
    QString fileName = ui->lineEditFileBegin->text();
    QString saveName = ui->lineEditFileEnd->text();

    CHECK_OPEN_FILE( fileName );
    CHECK_SAVE_PATH( saveName );

    QFile file(fileName);
    if( ! file.open( QFile::ReadOnly ) )
    {
        MES_INFORMATION( tr("提示"), tr("读取错误") );
        return;
    }
    QPolygonF poly;
    QTextStream fin(&file);
    QString tmp;
    while( ! fin.atEnd() )
    {
        tmp = fin.readLine();
        STR_NoSpace( tmp );
        getPointFromStr( poly, tmp );
    }

    QString wrongInfo = transform( poly, getOGR(fromPro), getOGR(destPro) );
    CHECK_WRONG_MES( wrongInfo );

    saveToFile( poly, saveName );
}

void Widget::saveToFile( const QPolygonF&poly, QString saveName )
{
    QFile file(saveName);
    if( ! file.open( QFile::WriteOnly ) )
    {
        MES_INFORMATION( tr("提示"), tr("保存错误") );
        return;
    }
    QTextStream fout(&file);
    fout.setRealNumberPrecision(15);
    foreach (QPointF pos, poly)
    {
        fout<<pos.x()<<","<<pos.y()<<CHANGE_LINE;
    }

    MES_INFORMATION( tr("提示"), tr("保存成功\n请查看文件") );
}

void Widget::on_buttonFileBegin_clicked()
{
    BUTTON_CLICKED_OPEN_FILE( ui->lineEditFileBegin );
}

void Widget::on_buttonFileEnd_clicked()
{
    BUTTON_CLICKED_SAVE_TXT( ui->lineEditFileEnd );
}
