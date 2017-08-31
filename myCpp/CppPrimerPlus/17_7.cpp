/*************************************************************************
	> File Name: 17_7.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月24日 星期五 15时07分49秒
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<string>
#include<iterator>
#include<vector>
#include<fstream>
#include<cstdlib>
using namespace std;
class Store
{
    ofstream &os;
public:
    Store(ofstream&s):os(s){}
    void operator()(const string&str)
    {
        size_t len=str.size();
        os.write((char*)&len,sizeof(size_t));
        os.write(str.data(),len);
    }
};
void GetStrs(ifstream&is,vector<string>&str);
void ShowStr(const string&);
int main()
{
    vector<string>vostr;
    string temp;
    cout<<"Enter strings (Empty line to quit):\n";
    while(getline(cin,temp)&&temp[0]!='\0')
    {
        vostr.push_back(temp);
    }
    cout<<"Here is your input:\n";
    for_each(vostr.begin(),vostr.end(),ShowStr);
    ofstream fout("strings.dat",ios_base::out|ios_base::binary);
    for_each(vostr.begin(),vostr.end(),Store(fout));
    fout.close();
    vector<string>vistr;
    ifstream fin("strings.dat",ios_base::in|ios_base::binary);
    if(!fin.is_open())
    {
        cerr<<"Could not open file for input.\n";
        exit(EXIT_FAILURE);
    }
    GetStrs(fin,vistr);
    cout<<"\nHere are the strings read from the file:\n";
    for_each(vistr.begin(),vistr.end(),ShowStr);
    return 0;
}
void ShowStr(const string&a)
{
    cout<<a<<endl;
}
void GetStrs(ifstream&is,vector<string>&str)
{
    char*s;size_t len;
    while(is.read((char*)&len,sizeof(size_t)))
    {
        s=new char[len];
        is.read(s,len);
        s[len+1]='\0';
        str.push_back(s);
        delete []s;
    }
}
