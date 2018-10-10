/*************************************************************************
	> File Name: 14_7_1.h
	> Author: 
	> Mail: 
	> Created Time: 2017年02月23日 星期四 16时57分16秒
 ************************************************************************/

#ifndef _14_7_1_H
#define _14_7_1_H

#include<iostream>
#include<valarray>
using namespace std;
class Wine
{
    string name;
    const int num;
    pair<valarray<int>,valarray<int>> Time;
public:
    Wine(const char*l,int y,const int yr[],const int bot[]):name(l),num(y),Time(valarray<int>(num),valarray<int>(num))
    {
        for(int i=0;i<num;i++)
        {
            Time.first[i]=yr[i];
            Time.second[i]=bot[i];
        }
    }
    Wine(const char*l,int y):name(l),num(y),Time(valarray<int>(num),valarray<int>(num))
    {
    }
    void GetBottles()
    {
        cout<<"Enter "<<name<<"data for "<<num<<" years(s):"<<endl;
        for(int i=0;i<num;i++)
        {
            cout<<"Enter year: ";cin>>Time.first[i];
            cout<<"Enter bottles for that year: ";cin>>Time.second[i];
        }
    }
    string&Label(){return name;}
    int sum(){return Time.second.sum();}
    void Show()
        {
                cout<<"Wine: "<<Label()<<endl;
                cout<<"\tYear\tBottles"<<endl;
            for(int i=0;i<num;i++)
            {
                cout<<"\t"<<Time.first[i]<<"\t"<<Time.second[i]<<endl;
            }
        }
};

#endif
