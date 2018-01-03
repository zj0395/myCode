#ifndef SHOWFORM_H
#define SHOWFORM_H

#include <QWidget>
#include "mainwidget.h"
#include <QCloseEvent>

class QStandardItemModel;

namespace Ui {
class ShowForm;
}

class ShowForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowForm(QWidget *parent = 0);
    ~ShowForm();

    void closeEvent(QCloseEvent *event);

    void setModelData(  QPoint pos, const VVDouble &m_layer1, const VVDouble &m_layer0, const VDouble &m_final );
private:
    Ui::ShowForm *ui;

    QStandardItemModel * m_layer1;
    QStandardItemModel * m_layer0;
    QStandardItemModel * m_final;

    void addOneRow(QStandardItemModel *model, const VDouble &result, QString title);

    static int id;
};

#endif // SHOWFORM_H
