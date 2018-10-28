/*************************************************************************
	> File Name: 25.cpp
	> Author: zj
	> Describe: 合并两个排序后的链表
	> Created Time: Wed 10 Oct 2018 09:29:18 AM CST
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
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if( pHead1 == NULL )
            return pHead2;
        if( pHead2 == NULL )
            return pHead1;
        ListNode begin(0);
        ListNode* cur = &begin;
        while( pHead1 != NULL && pHead2 != NULL )
        {
            if( pHead1->val <= pHead2->val )
            {
                cur->next = pHead1;
                pHead1 = pHead1->next;
            }
            else
            {
                cur->next = pHead2;
                pHead2 = pHead2->next;
            }
            cur = cur->next;
        }
        if( pHead1 == NULL )
            cur->next = pHead2;
        else
            cur->next = pHead1;
        return begin.next;
    }
};
