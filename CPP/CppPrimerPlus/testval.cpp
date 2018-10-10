/*************************************************************************
	> File Name: testval.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月23日 星期四 17时09分21秒
 ************************************************************************/

#include<iostream>
#include<valarray>
using namespace std;
int main()
{
    typedef std::valarray<int>ArrayInt;
    typedef pair<ArrayInt,ArrayInt>PairArray;
    PairArray pa(ArrayInt(2),ArrayInt(4));
    pa.first[0]=4;
    pa.first[1]=3;
    cout<<pa.first.sum()<<endl;
    return 0;
}
