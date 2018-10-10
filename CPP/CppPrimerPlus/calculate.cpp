#include "calculate.h"
inline int Strcal::anumber()
{
    return (int)str[a]-48;
}
double Strcal::Cal()
{
    for(;a<length;a++)
    {
        if(str[a]>='0'&&str[a]<='9')
        {
            num[numorder]=getnum();
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
    int rate=1;
    for(;a<length;a++)
    {
        if(str[a]=='.')
        {
            rate=0.1;
            numtemp+=rate*anumber();
            rate/=10;
        }
        else if(str[a]>='0'&&str[a]<='9')
        {
            if(rate==1)
            {   numtemp=anumber();rate=10;  }
            else if(rate>1)
                numtemp=anumber()+rate*numtemp;
            else if(rate<1)
                numtemp+=anumber()*rate;
        }
        else
        {
            --a;
            return numtemp;
        }
    }
}
void Strcal::getchar()
{
    for(;a<length;a++)
    {
        if(str[a]=='+'||str[a]=='-')
        {
            addminus[numorder]=str[a];
            numorder++;break;
        }
        else if(str[a]=='*')
        {
            ++a;
            num[numorder]*=getnextnum();
        }
        else if(str[a]=='/')
        {
            ++a;
            double temp=getnextnum();
            if(temp==0)
            {   std::cout<<"WRONG INPUT!"<<std::endl; temp=1;  }
            else
                num[numorder]/=temp;
        }
        else if(str[a]=='(')
        {
            num[numorder]=getnextnum();
        }
        else
        {--a;break;}
    }
}
double Strcal::getnextnum()
{
    for(;a<length;a++)
    {
        if(str[a]=='(')
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
            std::string newstr(&str[atemp],&str[a]);
            Strcal *ss=new Strcal(newstr);   
            return ss->Cal();
        }
        else if(str[a]>='0'&&str[a]<='9')
        {
            return getnum();
        }
    }
}
