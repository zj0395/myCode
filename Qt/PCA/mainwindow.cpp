#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QFileDialog>
#include<QMessageBox>
#include<QDebug>
#include"pca.h"
static bool do_pca(const std::string&a)
{
    std::ifstream testdata(a);
    std::ofstream fde_bug("pca_debug.txt");
    if(!testdata)
    {
        fde_bug<<"Can't open file: "<<a<<"\n";
        return 0;//打开失败则结束函数
    }
    int m=0,n=0;
    if(!(testdata>>m>>n))//读取行和列
    {
        fde_bug<<"Can non get rows and columns\n";
        testdata.close();
        fde_bug.close();
        return 0;
    }
    PCA pca(m,n);//eps与ratio可在此处显式定义
    //如PCA pca_t(m,n,0.0000001,0.95)，若未定义则默认为0.000001和0.9

    if(pca.getdata(testdata))//检查读取是否成功
    {
        testdata.close();
        std::ofstream fsout("pcaproject.txt");
        if(pca.haswrong().empty())//读取成功，检查是否有其它错误(jacobi计算失败)
        {
            pca.saveProject(fsout);//保存到文件
            fsout.close();
            pca.savechvalue(fde_bug);//调试，查看特征值
            pca.saveratio(fde_bug);//查看贡献率
            pca.savechvector(fde_bug);//查看特征向量
            pca.saveprin_load(fde_bug);
        }
        else
            fde_bug<<pca.haswrong();
    }
    else//读取失败(文件有错)进行提示
    {
        fde_bug<<pca.haswrong();
    }
    fde_bug.close();
    return 1;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PCA");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    const std::string temp=QFileDialog::getOpenFileName(this,"Open File","","*.txt").toStdString();
    //QString file=QFileDialog::getOpenFileName(this,"Open File","","*.txt");
    if(!temp.empty())
    {
        if(do_pca(temp))
            QMessageBox::information(this, tr("计算成功"), tr("计算结果已保存在pcaproject.txt中\n"
                                                          "其它值保存在pca_debug.txt中"));
        else
            QMessageBox::information(this, tr("计算失败"),
                                     tr("错误信息已记录在pca_debug.txt"));
    }
}
