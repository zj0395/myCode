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

    //一共有3个方案，所以这个数组有 7 个子数组
    //第一个数组是风险事件的输入框(A-D)，之后每两个分别是每个方案的风险(A1-D1)和权重(P1-P3)
    VQLineEdit edits[ 1 + PLAN_NUMBER*2 ];

    //综合评价结果的输入框
    VQLineEdit editsResult;

    //是否 空行视为0
    bool b_checkEmptyLine;

    //风险事件 和 预防方案 的切换窗口
    QTabWidget mainWidget;

    //方案1、方案2、方案3 的切换窗口
    QTabWidget planTab;

private:
    //生成 风险事件 的窗口
    QWidget *getPlanWidget();

    //生成 预防方案的窗口
    QWidget *getFirstWidget();

    //进行计算
    void doCalculate();

    //检查输入框是否为空
    bool checkEmpty();

    //结果显示
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
