#ifndef FORM_MAINWIDGET_H
#define FORM_MAINWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <vector>
#include <QString>
#include <QLineEdit>


typedef std::vector< double>   VDouble;

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

private:

    //第一个数组是总的设置(A-D)，之后每两个分别是每个方案的风险(A1-D1)和权重(P1-P4)
    VQLineEdit edits[ 1 + PLAN_NUMBER*2 ];
    VQLineEdit editsResult;

    bool b_checkEmptyLine;
    QTabWidget mainWidget;
    QTabWidget planTab;

private:
    QWidget *getPlanWidget();
    QWidget *getFirstWidget();

    void doCalculate();
    bool checkEmpty();

    void showResult(const VDouble &result, const VQString &inputResult);
};

class ShowWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit ShowWidget(const VDouble & result, const VQString & inputResult);
    ~ShowWidget();

    void closeEvent(QCloseEvent *event);

private:
    static int allID;
    const int myId;
};

#endif // FORM_MAINWIDGET_H
