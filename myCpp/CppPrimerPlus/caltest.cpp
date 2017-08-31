#include<iostream>
#include "calculate.h"
using namespace std;
int main()
{
    Strcal ss(string("(1/1*(4-3)+3)+(2/3-1/3)*3/(1+2)"));
    cout<<ss.Cal()<<endl;
    return 0;
}
