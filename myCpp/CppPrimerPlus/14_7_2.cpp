/*************************************************************************
	> File Name: 14_7_2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月23日 星期四 18时00分00秒
 ************************************************************************/

#include"14_7_1.h"
int main()
{
    cout<<"Enter name of wine: ";
    char lab[50];
    cin.getline(lab,49);
    cout<<"Enter number of years: ";
    int yrs;cin>>yrs;
    Wine holding(lab,yrs);
    holding.GetBottles();
    holding.Show();
    const int YRS=3;
    int y[YRS]={1993,1995,1998};
    int b[YRS]={48,60,72};
    Wine more("Gushing Grape Red",YRS,y,b);
    more.Show();
    cout<<"Total botles for "<<more.Label()<<": "<<more.sum()<<endl;
    cout<<"Bye\n";
    return 0;
}
