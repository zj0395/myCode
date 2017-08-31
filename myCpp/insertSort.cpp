#include<iostream>
using namespace std;
const int N=10;
void InsertSort(int*a,int n);
int main()
{
    int num[N]={76,32,187,12,9,67,52,123,4,25};
    InsertSort(num,N);
    for(int i=0;i<N;i++)cout<<num[i]<<" ";
    cout<<endl;
    return 0;
}
void InsertSort(int*a,int n)
{
    int temp=a[0];
    for(int i=1;i<n;i++)
    {
        temp=a[i];
        int j=i-1;
        while(j>=0&&a[j]>temp)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=temp;
    }
}
