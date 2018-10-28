/*************************************************************************
	> File Name: 1.cpp
	> Author: zj
	> Describe: 约瑟夫环，获取每一次的值
                n是人数，m是第几个
	> Created Time: Sat 13 Oct 2018 07:02:03 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
struct Node
{
    Node( int v ) : val(v), next(NULL){}
    int val;
    Node* next;
};

class Solution
{
public:
    Solution(){nodes=NULL;}
    ~Solution(){delete nodes;}
    void begin( int n, int M )
    {
        nums = n;
        initNodes(n);
        getOutPut(nodes, M);
    }
    void print()
    {
        for( auto iter=result.begin(); iter!=result.end(); ++iter )
            cout<< *iter<<" ";
        cout<<"\n";
    }
private:
    void getOutPut( Node* begin, int M )
    {
        if( result.size() == nums )
            return;
        if( begin == begin->next )
        {
            result.push_back(begin->val);
            return;
        }
        Node* tmp = NULL;
        for( int i=0; i<M; ++i )
        {
            if( i == M-1 )
                tmp = begin;
            begin = begin->next;
        }
        result.push_back(begin->val);
        tmp->next = begin->next;
        delete begin;
        getOutPut( tmp->next, M );
    }
    void initNodes( int n )
    {
        Node* tmp = NULL;
        for( int i=0; i<n; ++i )
        {
            if( nodes == NULL )
            {
                nodes = new Node(i+1);
                tmp = nodes;
            }
            else
            {
                Node* t = new Node(i+1);
                tmp->next = t;
                tmp = t;
            }
        }
        tmp->next = nodes;
        tmp = nodes;
    }
    vector<int> result;
    Node* nodes;
    int nums;
};

int main()
{
    int t;
    int n, m;
    cin>>t;
    while( t-- )
    {
        cin>>n>>m;
        Solution s;
        s.begin( n, m-1 );
        s.print();
    }
}
