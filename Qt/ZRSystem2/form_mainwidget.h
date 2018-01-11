#ifndef FORM_MAINWIDGET_H
#define FORM_MAINWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <vector>
#include <QString>
#include <QLineEdit>


typedef std::vector< QString>  VQString;
typedef std::vector<VQString> VVQString;
typedef std::vector<QLineEdit*> VQLineEdit;


#define PLAN_NUMBER 3

class Form_MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Form_MainWidget(QWidget *parent = 0);
    ~Form_MainWidget();

    QWidget *getPlanWidget();
    QWidget *getFirstWidget();

    void doCalculate();
    bool checkEmpty();

private:

    //第一个数组是总的，之后每两个分别是每个方案的风险和权重
    VQLineEdit edits[ 1 + PLAN_NUMBER*2 ];
    VQLineEdit editsResult;

    bool b_checkEmptyLine;
};

#endif // FORM_MAINWIDGET_H
