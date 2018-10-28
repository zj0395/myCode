/*************************************************************************
	> File Name: 30.cpp
	> Author: zj
	> Describe: 能得到栈中最小元素的数据结构，包含min函数的栈
	> Created Time: Wed 10 Oct 2018 10:46:48 AM CST
 ************************************************************************/

#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    void push(int value) {
        dataStack.push(value);
        minStack.push( minStack.empty() ? value : std::min( min(), value ) );
    }
    void pop() {
        dataStack.pop();
        minStack.pop();
    }
    int top() {
        return dataStack.top();
    }
    int min() {
        return minStack.top();
    }
private:
    stack<int> dataStack;
    stack<int> minStack;
};
