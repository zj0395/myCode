#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <vector>
#include <QString>

class QTabWidget;
class QHBoxLayout;
class QGridLayout;
class QLineEdit;

typedef std::vector<QString> VQStr;   //1D array
typedef std::vector<VQStr>   VVQStr;  //2D array

typedef std::vector<double>  VDouble;
typedef std::vector<VDouble> VVDouble;

typedef std::vector<int>     VInt;
typedef std::vector< QLineEdit* > VLineEdit;

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
    void on_pushButton_clicked();

private:
    Ui::MainWidget *ui;
    VLineEdit layer0;
    VLineEdit layer1;
    VLineEdit layer2;
    VLineEdit score2;

private:
    QWidget *addLayoutToWidget(const VQStr &content);
    QHBoxLayout *newLayout(int layer);
    void addWeidht(QGridLayout *gLayout, QString str, int row, VLineEdit& layer);

    void information(QString title, QString content);

    bool checkLineEdit();
    double getDegree(int idx, double score);
    VDouble getLayerResult(VDouble &oneWeigths, VVDouble &degress, int beginIdx, int num);
};

#endif // MAINWIDGET_H
