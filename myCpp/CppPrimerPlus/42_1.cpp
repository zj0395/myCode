/*************************************************************************
	> File Name: 42_1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月26日 星期日 19时43分16秒
 ************************************************************************/

#include<iostream>
#include<vector>
template<typename T>
class Showsomething{
private:
    vector<T> a;
public:
    Showsomething(vector<T>ss):a(ss){}
    void print()
    {
        if(cc.size()>=2){
            T::const_iterator iter(cc.begin());
            ++iter;
            T value=*iter;
            std::cout<<value<<endl;
        }
    }
};
int main()
{
    vector<string>a={"you are good","you fucking","motherfucker"};
    Showsomething<string>ss(a);
    a.print();
    return 0;
}
