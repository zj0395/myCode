#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <vector>
#include <QString>

class QTabWidget;
class QHBoxLayout;
class QGridLayout;
class QLineEdit;

typedef std::vector<QString> VQStr;    //字符串一维数组
typedef std::vector<VQStr>   VVQStr;   //字符串二维数组

typedef std::vector<double>  VDouble;  //浮点数一维数组
typedef std::vector<VDouble> VVDouble; //浮点数二维数组

typedef std::vector<int>     VInt;     //整数一维数组
typedef std::vector< QLineEdit* > VLineEdit; //输入框的一维数组

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    //当按下 开始计算 按钮时的函数
    void on_pushButton_clicked();

private:
    Ui::MainWidget *ui;
    VLineEdit layer0;//第一层的权重的所有输入框，按顺序排列
    VLineEdit layer1;//第二层的权重的所有输入框，按顺序排列
    VLineEdit layer2;//第三层的权重的所有输入框，按顺序排列

    VLineEdit score2;//第三层的得分的所有输入框，按顺序排列

private:

    //第三层的选项卡窗口
    QWidget *newChildWidget(const VQStr &content);

    //生成第 一/二/三 层的输入, layer 代表层号
    QHBoxLayout *newLayout(int layer);

    //生成 权重或得分 和 对应的输入框, 并保存到数组里
    void addWeidht(QGridLayout *gLayout, QString str, int row, VLineEdit& layer);

    //提示的小窗口信息
    void information(QString title, QString content);

    //检查输入框是否为空
    bool checkLineEdit();

    //根据序号和得分，返回该得分的隶属度
    double getDegree(int idx, double score);

    //该函数进行矩阵相乘
    VDouble getLayerResult(VDouble &oneWeigths, VVDouble &degress, int beginIdx, int num);

    //测试函数，不用管
    void testGetDegree();

    //读取 ini 配置文件，未使用，不用管
    void readIniFile();

    //把结果保存成文件
    void saveResult(QString str, const VVDouble &layer1, const VVDouble &layer0, const VDouble &final);

    //把结果显示在另一个窗口上
    void showResult(const VVDouble &layer1, const VVDouble &layer0, const VDouble &final);
};

#endif // MAINWIDGET_H
