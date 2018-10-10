/*************************************************************************
	> File Name: 24.cpp
	> Author: zj
	> Describe: 翻转链表，头插法
	> Created Time: Wed 10 Oct 2018 09:21:19 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        ListNode ret(0);
        while( pHead != NULL )
        {
            ListNode* tmp = pHead->next;
            pHead->next = ret.next;
            ret.next = pHead;
            pHead = tmp;
        }
        return ret.next;
    }
};
