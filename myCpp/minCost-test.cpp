#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits.h>
using namespace std;

int minCost_except(vector<vector<int>>& costs, int nBegin, int Kexcept)
{
    if( nBegin == costs.size()  )
        return 0;
    vector<int> mins( costs[nBegin] );
    for(int i=0; i<costs[0].size(); ++i)
    {
        if( i == Kexcept )
            mins[i] = -1;
        else
            mins[i] += minCost_except(costs, nBegin+1, i);
    }
    int min = mins[0];
    for( int i=0; i<mins.size(); ++i)
    {
        if( min == -1  )
        {
            min = mins[i];
            continue;
        }
        if( mins[i] != -1 )
            min = mins[i] < min ? mins[i] : min;
    }
    return min;
}

/** 请完成下面这个函数，实现题目要求的功能 **/
 /** 当然，你也可以不按照这个模板来作答，完全按照自己的想法来 ^-^  **/
int minCost(vector<vector<int>>& costs)
{
    return minCost_except( costs, 0, -1 );
}

int main()
{
	int N,K;
	int cost;
	vector<vector<int> > costs;
	string s;
	istringstream is;

	getline(cin, s);
	is.str(s);
	is>>N>>K;
	for(int i =0 ; i < N; i++)
	{
		vector<int> t;
		getline(cin, s);
		is.clear();
		is.str(s);
		for(int j = 0; j < K; j++) {
			is >> cost;
			t.push_back(cost);
		}
		costs.push_back(t);
	}
	cout<<minCost(costs)<<endl;
	return 0;
}
