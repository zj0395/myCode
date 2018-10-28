/*************************************************************************
	> File Name: 66.cpp
	> Author: zj
	> Describe: 构建乘积数组，不使用除法
                B[i] = A[0]*A[1]*...A[i-1]*A[i+1]*...A[n]
	> Created Time: Thu 11 Oct 2018 09:00:40 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        vector<int> ret( A.size(), 0 );
        for( int i=0, product=1; i<A.size(); product*=A[i], ++i )
            ret[i] = product;
        for( int i=A.size()-1, product=1; i>=0; product*=A[i], --i )
            ret[i] *= product;
        return ret;
    }
};
