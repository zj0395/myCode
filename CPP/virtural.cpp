/*************************************************************************
	> File Name: virtural.cpp
	> Author: zj
	> Describe: 虚函数表, 64位系统，所以使用 long long
	> Created Time: Tue 16 Oct 2018 08:57:19 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

class A
{
public:
    virtual void f()
    {
        cout<<"A::f\n";
    }
};

class B:public A
{
    virtual void f2()
    {
        cout<<"B::f2\n";
    }
};

class C:public A
{
    virtual void f()
    {
        cout<<"C::f\n";
    }
    virtual void f2()
    {
        cout<<"C::f2\n";
    }
};

class D:public C, B
{
};

void f()
{
    cout<<"f\n";
}

int main()
{
    typedef void (*Fun)(void);
    Fun funa, funb1, funb2 ;

    A a;
    funa = (Fun)*(long long*)*(long long*)(&a);
    cout<<"funa: "<<(long long*)*(long long*)(&a)<<"\n";
    funa();

    B b;
    funb1 = (Fun)(*( (long long*)*(long long*)(&b) ));
    funb2 = (Fun)(*( (long long*)*(long long*)(&b)+1 ));
    cout<<"funb1: "<<( (long long*)*(long long*)(&b) )<<"\n";
    funb1();
    cout<<"funb2: "<<( (long long*)*(long long*)(&b)+1 )<<"\n";
    funb2();

    D d;
    Fun d1, d2, d3, d4;
    // 第一个虚函数表
    d1 = (Fun)*((long long*)*(long long*)(&d));
    cout<<"d1: "<<((long long*)*(long long*)(&d))<<"\n";
    d1();
    d2 = (Fun)*((long long*)*(long long*)(&d)+1);
    cout<<"d2: "<<((long long*)*(long long*)(&d)+1)<<"\n";
    d2();

    // 第二个虚函数表
    d3 = (Fun)*((long long*)*((long long*)(&d)+1));
    cout<<"d3: "<<((long long*)*((long long*)(&d)+1))<<"\n";
    d3();
    d4 = (Fun)*((long long*)*((long long*)(&d)+1)+1);
    cout<<"d4: "<<((long long*)*((long long*)(&d)+1)+1)<<"\n";
    d4();

    A* da = (C*)&d;
    cout<<"(C*)&d: "<<da<<"\n";
    da->f();
    da = (B*)&d;
    cout<<"(B*)&d: "<<da<<"\n";
    da->f();

    cout<<&d<<"\n"; // same with (C*&d)
    cout<<(&d)+1<<"\n"; // same with (B*)&d

    return 0;
}
