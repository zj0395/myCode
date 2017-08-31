#ifndef _CALCULATE_H
#define _CALCULATE_H

#include<QString>
//#include <QDebug>
namespace _calculate
{

const int LIMIT=50;
const double PI=3.1415926535898;
const double E=2.718281828459;
class Strcal
{
public:
    Strcal(const QString &st):str(st),length(st.size()),a(0),result(0.0),numorder(0){
        num=new double[LIMIT]{0};      addminus=new QChar[LIMIT];   }
    Strcal(Strcal&ss):str(ss.str),length(ss.length),a(0),result(0.0),numorder(0)
    {
        num=new double[LIMIT]{0};addminus=new QChar[LIMIT];
    }


    ~Strcal();
    double Cal();
    const QString& WhatIsWrong()const;
private:
    const QString str;
    const int length;
    int a;//迭代器
    double result;
    double *num;//存储数字
    int numorder;//存储数字的顺序 
    QChar *addminus;//only + and -
    QString wronginfo;

    //private way
    int anumber();//a指向的数字
    double getnum();
    void getchar();
    double getnextnum(double n);
    double dealbracket(double n);//n is default return value, 1 or 0
};
}

namespace _calname {

    const static QString sqr="√11";
    const static QString pi="π";

    double calfact(double n);//阶乘
    int calintfact(int n);
    double caldoublefact(double n);//此坑待填
    double Gamma(double x);
}

#endif
