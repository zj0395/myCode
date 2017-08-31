#ifndef _PCA_H
#define _PCA_H

#include<vector>
#include<fstream>
class PCA
{
public:
    typedef std::vector<double>vdouble;//一维数组，下一个为二维数组
    typedef std::vector<vdouble>vvdouble;//以上两个typedef只能在类内部使用
    PCA(int m,int n,double e=0.000001,double g=0.9);
    ~PCA(){delete p_data;}

    //接口只有3个，应按顺序执行
    bool getdata(std::ifstream&);
    void saveProject(std::ofstream&);
    const std::string& haswrong()
    {return wronginfo;}

    //调试函数
    void showdata()const;//cout数据
    void showmatrixcov()const;//cout协方差矩阵
    void showchvalue()const;//cout特征值
    void showchvector(int m=0)const;//cout特征矩阵
    void showratio()const;//cout贡献率
    void showprin_load()const;//cout主成分载荷


    void savedata(std::ofstream& fcout)const;//cout数据
    void savematrixcov(std::ofstream& fcout)const;//cout协方差矩阵
    void savechvalue(std::ofstream& fcout)const;//cout特征值
    void savechvector(std::ofstream& fcout)const;//cout特征矩阵
    void saveratio(std::ofstream& fcout)const;//cout贡献率
    void saveprin_load(std::ofstream &fcout)const;//cout主成分载荷
private:
    struct PCA_Data//该结构只能在PCA类内部使用
    {
        PCA_Data(const int );
        //数据公有
        vvdouble matrixcov;//协方差矩阵
        vdouble chvalue;//特征值
        vvdouble chvector;//特征向量
        vdouble value_ratio;//特征值贡献率
        vvdouble prin_load;//主成分载荷
    };

    //私有函数
    void standarddata();//数据标准化
    void matrixproduct();//求解协方差矩阵
    void jcb();//求特征值和特征向量
    void selectionsort();//特征值排序
    void calprincipal_loading();//计算主成分载荷
    int selectcharactor();
    vvdouble setScores();

    //数据
    const int rows;
    const int columns;
    vvdouble data;//标准化的数据
    PCA_Data* p_data;
    std::string wronginfo;
    int t;//运算后维度
    int l;//jcb times
    const double eps;
    const double getratio;
};

#endif
