/*************************************************************************
	> File Name: 17_2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月24日 星期五 14时39分53秒
 ************************************************************************/

#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    ifstream fin;
    fstream fout;
    char ch;
    fin.open("17_2.txt");
    fout.open("17_2_1.txt",ios_base::out|ios_base::app);
    fout<<"Here is what you what"<<endl;
    while(!fin.eof())
    {
        fin>>ch;
        fout<<ch;
    }
    return 0;
}
