#ifndef QUERYFORM_H
#define QUERYFORM_H

#include <QWidget>
#include "sql.h"

namespace Ui {
class QueryForm;
}

class QueryForm : public QWidget
{
    Q_OBJECT

public:
    explicit QueryForm(QWidget *parent = 0);
    ~QueryForm();

private slots:

    void on_butonGet_clicked();

    void on_buttonSet_clicked();

private:
    Ui::QueryForm *ui;

    Sql * sql;
};

#endif // QUERYFORM_H
