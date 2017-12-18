#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "sql.h"

namespace Ui {
class LoginForm;
}

class QueryForm;

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private slots:
    void on_buttonLogin_clicked();

    void on_buttonReg_clicked();

private:
    Ui::LoginForm *ui;

    Sql *sql;

    QueryForm * queryForm;
};

#endif // MAINFORM_H
