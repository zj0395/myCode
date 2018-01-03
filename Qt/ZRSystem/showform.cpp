#include "showform.h"
#include "ui_showform.h"
#include <QStandardItemModel>
#include <QTableView>

# pragma execution_character_set("utf-8")//可以使用中文

extern const VQStr  rule1;
extern const VQStr  rule0 ;
extern const VInt   rule1_Num;
extern const int    DegreeSize = 5;

int ShowForm::id = 0;

extern QString getIdx( int layer1Idx )
{
    int allIdx = 0;
    int first=0, second=0;
    for( ; first<rule1_Num.size(); ++first )
    {
        second=0;
        int num = rule1_Num[first];
        for( ; second<num && allIdx<layer1Idx; ++second )
            ++allIdx;
        if(  allIdx == layer1Idx && second != num )
            break;
    }
    QString numID = QString("%1-%2").arg(first+1).arg(second+1);
    return "R"+numID;
}


ShowForm::ShowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowForm)
{
    ui->setupUi(this);

    this->setWindowTitle( QString("评价结果%1").arg(++id) );

    m_layer1 = new QStandardItemModel();
    m_layer0 = new QStandardItemModel();
    m_final  = new QStandardItemModel();

    QStandardItemModel * models[3] = { m_layer1, m_layer0, m_final };
    QTableView         * views [3] = { ui->viewLayer1, ui->viewLayer0, ui->viewFinal};
    QString              title [3] = { "要素层结果", "准则层结果", "目标层结果" };

    for( int i=0; i<3; ++i )
    {
        models[i]->setColumnCount( 2 );
        models[i]->setHorizontalHeaderItem( 0, new QStandardItem( title[i]) );
        models[i]->setHorizontalHeaderItem( 1, new QStandardItem( "评价结果") );

        views[i]->setModel( models[i] );
        views[i]->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        views[i]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void ShowForm::addOneRow( QStandardItemModel * model, const VDouble & result, QString title )
{
    static const QString Level[5] = {"很差", "较差", "一般", "较好", "很好"};
    int    maxIdx   = 0;
    double maxValue = result[0];
    for( int idx = 1; idx<DegreeSize; ++idx )
    {
        if( result[idx] > maxValue )
            maxIdx = idx;
    }

    QList<QStandardItem*> list;
    list.append( new QStandardItem( title ) );
    list.append( new QStandardItem( Level[maxIdx] ) );
    foreach (QStandardItem* item, list) {
        item->setTextAlignment( Qt::AlignCenter );
    }
    model->appendRow( list );
}

void ShowForm::setModelData( QPoint pos, const VVDouble &layer1, const VVDouble &layer0, const VDouble &final)
{
    for( int i=0; i<layer1.size(); ++i )
    {
        addOneRow( m_layer1, layer1[i], rule1[i] + getIdx(i) );
    }

    for( int i=0; i<layer0.size(); ++i )
    {
        addOneRow( m_layer0, layer0[i], rule0[i] + QString("R%1").arg(i+1) );
    }

    addOneRow( m_final, final, "目标层结果" );

    this->move( pos );
    show();
}

ShowForm::~ShowForm()
{
    delete ui;
}

void ShowForm::closeEvent(QCloseEvent *event)
{
    delete this;
}
