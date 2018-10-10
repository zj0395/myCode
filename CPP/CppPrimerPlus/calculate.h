#ifndef _CALCULATE_H
#define _CALCULATE_H

#include<iostream>
const int LIMIT=50;
class Strcal
{
public:
    Strcal(const std::string st):str(st),length(st.size()),a(0),result(0.0),numorder(0){num=new double[LIMIT];addminus=new char[LIMIT];}
    double Cal();
private:
    std::string str;
    int length;
    int a;//迭代器
    double result;
    double *num;//存储数字
    int numorder;//存储数字的顺序 
    char *addminus;//only + and -

    //privasse way
    int anumber();//a指向的数字
    double getnum();
    void getchar();
    double getnextnum();
};

#endif
