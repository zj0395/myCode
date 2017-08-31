#include "calculate.h"
#include <cmath>

using namespace _calculate;
#define numnow num[numorder]

Strcal::~Strcal()
{
    delete []num;
    delete []addminus;
}

inline int Strcal::anumber()
{
    return str[a].unicode()-48;
}
const QString& Strcal::WhatIsWrong()const
{
    return wronginfo;
}
double Strcal::Cal()
{
    for(;a<length;a++)
    {
        if(str[a]>='0'&&str[a]<='9')
        {
            numnow=getnum();
        }
        else 
            getchar();
    }
    result=num[0];
    for(int i=1;i<=numorder;i++)
    {
        if(addminus[i-1]=='+')
            result+=num[i];
        else if(addminus[i-1]=='-')
            result-=num[i];
    }
    return result;
}
double Strcal::getnum()
{
    double numtemp=0;
    double numberrate=1;
    for(;a<length;a++)
    {
        if(str[a]=='.')
        {
            numberrate=0.1;
        }
        else if(str[a]>='0'&&str[a]<='9')
        {
            if(numberrate==1)
            {   numtemp=anumber();numberrate=10;  }
            else if(numberrate>1)
                numtemp=anumber()+numberrate*numtemp;
            else if(numberrate<1)
            {   numtemp=anumber()*numberrate+numtemp;     numberrate/=10;}
        }
        else
        {
            --a;
            break;
        }
    }
    return numtemp;
}
void Strcal::getchar()
{
    for(;a<length;a++)
    {
        if(str[a]=='+'||str[a]=='-')
        {
            addminus[numorder]=str[a];
            numorder++;
            break;
        }
        else if(str[a]=='*')
        {
            ++a;
            if(a==1)numnow=1;
            numnow*=getnextnum(1);
        }
        else if(str[a]=='/')
        {
            ++a;
            if(a==1)numnow=1;
            double temp=getnextnum(1);
            if(temp==0)
            {
                throw(QString("=∞"));
            }
            else
                numnow/=temp;
        }
        else if(str[a]=='(')
        {
            if(numnow==0)
            {
                numnow=dealbracket(0);
            }
            else
                numnow*=dealbracket(1);
        }
        else if(str[a]=='^')
        {
            ++a;
            numnow=std::pow(numnow,getnextnum(1));
        }
        else if(str[a]=='!')
        {
            numnow=_calname::calfact(numnow);
        }
        else if(str[a]==_calname::pi[0])
        {
            if(numnow==0)
                numnow=PI;
            else
                numnow*=PI;
        }
        else if(str[a]=='e')
        {
            if(numnow==0)
                numnow=E;
            else
            {
                a++;
                numnow*=std::pow(10,getnextnum(0));
            }
        }
        else if(str[a]==_calname::sqr[0])
        {
            a++;
            if(numnow==0)
                numnow=std::sqrt(getnextnum(0));
            else
                numnow*=std::sqrt(getnextnum(1));
        }
        else if(str[a]=='s'&&str[a+1]=='i'&&str[a+2]=='n')
        {
            a+=3;
            if(numnow==0)
                numnow=std::sin(PI*getnextnum(0)/180);
            else
                numnow*=std::sin(PI*getnextnum(0)/180);
        }
        else if(str[a]=='c'&&str[a+1]=='o'&&str[a+2]=='s')
        {
            a+=3;
            if(numnow==0)
                numnow=cos(PI*getnextnum(0)/180);
            else
                numnow*=cos(PI*getnextnum(0)/180);
        }
        else if(str[a]=='t'&&str[a+1]=='a'&&str[a+2]=='n')
        {
            a+=3;
            if(numnow==0)
                numnow=tan(PI*getnextnum(0)/180);
            else
                numnow*=tan(PI*getnextnum(0)/180);
        }
        else if(str[a]=='l'&&str[a+1]=='n')
        {
            a+=2;
            double temp=getnextnum(1);
            if(temp==0)
            {
                throw(QString("=-∞"));
            }
            else if(numnow==0)
                numnow=log(temp);
            else
                numnow*=log(temp);
        }
        else if(str[a]=='l'&&str[a+1]=='g')
        {
            a+=2;
            double temp=getnextnum(1);
            if(temp==0)
            {
                throw(QString("=-∞"));
            }
            else if(numnow==0)
                numnow=log10(temp);
            else
                numnow*=log10(temp);
        }
        else if(str[a]>='0'&&str[a]<='9')
        {
            --a;
            break;
        }
        else
        {
            continue;
        }
    }
}
double Strcal::dealbracket(double n)
{
    int atemp=a+1;
    int temp=1;
    for(++a;a<length;a++)
    {
        if (str[a]=='(')
            ++temp;
        else if(str[a]==')')
        {
            --temp;
            if(temp==0)
                break;
        }
    }
    QString newstr=str.mid(atemp,a-atemp);
    if(newstr.isEmpty())
     {   return n;}
    else
    {
        Strcal* ss=new Strcal(newstr);
        double ress=ss->Cal();
        delete ss;
        return ress;
    }
}

double Strcal::getnextnum(double n)
{
    for(;a<length;a++)
    {
        if(str[a]=='(')
        {
            return dealbracket(n);
        }
        else if(str[a]>='0'&&str[a]<='9')
        {
            return getnum();
        }
        else if(str[a]==_calname::pi[0])
        {
            return PI;
        }
        else if(str[a]=='e')
        {
            return E;
        }
        else if(str[a]=='-')
        {
            ++a;
            return 0-getnextnum(n);
        }
        else if(str[a]==_calname::sqr[0])
        {
            ++a;
            return std::sqrt(getnextnum(n));
        }
    }
    wronginfo=("Error: Less a number.");
    return n;
}

double _calname::calfact(double n)
{
    if(n==(int)n)
    {
        return calintfact((int)n);
    }
    else
    {
        return caldoublefact(n);
    }
}
int _calname::calintfact(int n)
{
    if(n==0)
        return 1;
    else return n*calintfact(n-1);
}
double _calname::caldoublefact(double n)
{
    if(n<1)
        return n*Gamma(n);
    else
        return n*caldoublefact(n-1);
}
double _calname::Gamma(double x)
{
    int i;
    double y,t,s,u;
    static double a[11]={ 0.0000677106,-0.0003442342, 0.0015397681,
                         -0.0024467480, 0.0109736958,-0.0002109075,
                          0.0742379071, 0.0815782188, 0.4118402518,
                          0.4227843370, 1.0};
    if (x<=0.0)
    {
        return(-1.0);
    }

    y=x;
    if (y<=1.0)
    {
        t=1.0/(y*(y+1.0));
        y=y+2.0;
    }
    else
        if(y<=2.0)
        {
            t=1.0/y;
            y=y+1.0;
        }
        else
            if(y<=3.0)
            {
                t=1.0;
            }
            else
            {
                t=1.0;
                while (y>3.0)
                {
                    y=y-1.0;
                    t=t*y;
                }
            }
    s=a[0];
    u=y-2.0;
    for (i=1; i<=10; i++)
    {
        s=s*u+a[i];
    }
    s=s*t;
    return(s);
}
