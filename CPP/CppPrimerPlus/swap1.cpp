/*************************************************************************
	> File Name: test1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月25日 星期六 18时57分23秒
 ************************************************************************/

#include<iostream>
#include<vector>
using std::string;
namespace ss{
template<typename T>
class Widge
{
private:
    int a,b;
    std::vector<T> vest;
public:
    Widge(T&a2,T&b2):a(3),b(4)
    {
        vest.push_back(a2);
        vest.push_back(b2);
    }
    void sh()const
    {
        std::cout<<vest[0]<<vest[1]<<std::endl;
    }
};
template<typename T>
class Name
{
    Widge<T>*st;
public:
    Name(T&s,T&e)
    {
        st=new Widge<T>(s,e);
    }
    Name(const Name&s)
    {
        st=s.st;
    }
    Name&operator =(const Name&rhs)
    {
        *st=*(rhs.st);
    }
    void swap(Name&another)
    {
        using std::swap;
        swap(st,another.st);
    }
    void show()const
    {
        st->sh();
    }
};
        template<typename T>
        void swap(Name<T>&a,Name<T>&b)
        {
            a.swap(b);
        }
    }
int main()
{
    string s1="you good",s2="you fuck";
    string s3="thanks",s4="sgeaq";
    using ss::Name;
    Name<string> a1(s3,s4);
    Name<string>a2(s1,s2);
    a1.show();
    using std::swap;
    swap(a1,a2);
    a1.show();
    a2.show();
    return 0;
}
