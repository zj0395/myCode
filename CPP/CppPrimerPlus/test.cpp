/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年03月05日 星期日 16时46分00秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Test{
private:
    int *i;
public:
    Test():i(new int[3]){i[0]=0;i[1]=3;i[2]=5;};
    void show(){using m=i;cout<<m[1];}
};
int main()
{
    Test ms;
    ms.show();
    return 0;
}
