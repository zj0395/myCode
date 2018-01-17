#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QRegularExpression>
#include <QDebug>
#include <QMessageBox>

typedef std::vector<QString> VQStr;
typedef std::vector<VQStr>   VVQStr;

#define BUTTON_CLICKED_OPEN( lienEdit )\
{\
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择"), "" );\
    if( !fileName.isEmpty() )\
        lienEdit->setText( fileName );\
}
#define BUTTON_CLICKED_SAVE( lienEdit )\
{\
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), "" );\
    if( !fileName.isEmpty() )\
        lienEdit->setText( fileName );\
}

#define MES_INFORMATION( title, content )\
{\
    QMessageBox::information( this, title, content );\
}

#define CHECK_SAVE( resultPath )\
{\
    if( resultPath.isEmpty() )\
    {\
        MES_INFORMATION( tr("提示"), tr("未设置保存位置") );\
        return;\
    }\
}

#define CHECK_OPEN( imgPath )\
{\
    if( imgPath.isEmpty() )\
    {\
        MES_INFORMATION( tr("提示"), tr("未选择文件") );\
        return;\
    }\
    if( ! QFileInfo(imgPath).exists() )\
    {\
        MES_INFORMATION( tr("提示"), tr("文件 %1 不存在").arg(imgPath) );\
        return;\
    }\
}

//删除空格
inline void STR_NoSpace(QString & str)
{
    str = str.simplified();
    str.remove(' ');
}

VQStr resolveOneLine(QString oneLine , QString &wrongInfo);
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

VQStr resolveOneLine( QString oneLine, QString & wrongInfo )
{
    VQStr ret;
    const int timeStrSize = 14;

    if( oneLine.size() < timeStrSize  )
    {
        wrongInfo = "Too Short";
        return ret;
    }

    QString timeStr = oneLine.left( timeStrSize );
    oneLine = oneLine.mid( timeStrSize+1 );

    const static QString regExp = "([\\d]+[\\.][\\d][\\d])"
                                  "([ 0-]+)"
                                  "([\\d]+[\\.][\\d][\\d])"
                                  "([\\d 0\\-\\.]*)"
                                  "(.*)";
    const static int DEST_NUM    = 3;
    const static int DEST[DEST_NUM] = {1, 3, 5};
    const static QRegularExpression bandIdxExp(regExp);

    QRegularExpressionMatch match = bandIdxExp.match( oneLine );

    qDebug()<<timeStr;
    ret.push_back( timeStr );
    if( match.hasMatch() )
    {
        for( int i=0; i<DEST_NUM; ++i )
        {
            QString str  = match.captured( DEST[i] );
            STR_NoSpace( str );
            ret.push_back( str );
            qDebug()<<str;
        }
    }
    else
    {
        wrongInfo = "Wrong";
    }
    return ret;
}

QString resolve( QString txtPath, QString savePath )
{
    VVQStr readData;
    QString wrongInfo;

    QFile file(txtPath);
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QTextStream fin(&file);
        QString line = fin.readLine();

        int lineNum = 0;

        while ( !line.isNull() )
        {
            ++lineNum;
            line = line.simplified();
            if( line.isEmpty() )
            {
                wrongInfo += QString("Line:%1 Empty\n").arg(lineNum);
            }
            else
            {
                QString oneWrongInfo;
                readData.push_back( resolveOneLine( line, oneWrongInfo ) );
                if( ! oneWrongInfo.isEmpty() )
                {
                    wrongInfo += QString("Line:%1 %2\n").arg(lineNum).arg(oneWrongInfo);
                }
            }
            line = fin.readLine();
        }
    }
    else
    {
        wrongInfo = "Fail To Open File";
    }
    file.close();

    QFile outFile( savePath );
    if ( outFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text) )
    {
        QTextStream fout(&outFile);
        for( int i=0; i<readData.size(); ++i )
        {
            VQStr & oneLine = readData[i];
            for( int j=0; j<oneLine.size(); ++j )
            {
                fout<<oneLine[j]<<",";
            }
            fout<<"\n";
        }
    }
    outFile.close();

    return wrongInfo;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonOPen_clicked()
{
    BUTTON_CLICKED_OPEN( ui->lineEditOpen );
}

void Widget::on_pushButtonSave_clicked()
{
    BUTTON_CLICKED_SAVE( ui->lineEditSave );
}

void Widget::on_pushButtonDo_clicked()
{
    QString txtPath = ui->lineEditOpen->text();
    QString savePath = ui->lineEditSave->text();

    CHECK_OPEN( txtPath );
    CHECK_SAVE( savePath );

    QString wrongInfo = resolve( txtPath, savePath );

    if( ! wrongInfo.isEmpty() )
    {
        MES_INFORMATION( tr("错误"), wrongInfo )
    }
    else
    {
        MES_INFORMATION( tr("完成"), tr("请查看文件") )
    }
}
