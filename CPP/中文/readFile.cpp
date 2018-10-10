#include <fstream>
#include <iostream>
using namespace std;
int main()
{
    ofstream fout("./中文名称.txt");
    fout<<"中文\n"<<"Good";
    cout<<fout.is_open()<<endl;
    fout.close();
    return 0;
}
