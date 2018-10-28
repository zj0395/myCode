/*************************************************************************
	> File Name: 22.cpp
	> Author: zj
	> Describe: 链表中倒数第K个节点
	> Created Time: Wed 10 Oct 2018 08:38:05 AM CST
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
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if( pListHead == NULL )
            return NULL;
        ListNode* pHead1 = pListHead;
        while( pHead1 != NULL && k != 0  )
        {
            --k;
            pHead1 = pHead1->next;
        }
        if( k > 0 )
            return NULL;
        while( pHead1 != NULL )
        {
            pListHead = pListHead->next;
            pHead1 = pHead1->next;
        }
        return pListHead;
    }
};
