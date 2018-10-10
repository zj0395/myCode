/*************************************************************************
	> File Name: c8_1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年03月15日 星期三 21时54分42秒
 ************************************************************************/

#include<vector>
#include<sstream>
#include<iostream>
#include<fstream>
using namespace std;
ifstream& readstr(ifstream&is)
{
    string str;
    vector<string>svec;
    while(getline(is,str))
    {
        svec.push_back(str);
    }
    for(string&s:svec)
    {   
        istringstream recode(s);
        while(recode>>str)
        cout<<str;
    }
    is.clear();
    return is;
}
int main()
{
    ifstream ifs("text");
    readstr(ifs);
    return 0;
}
