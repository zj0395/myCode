/*************************************************************************
	> File Name: 23.cpp
	> Author: zj
	> Describe: 链表中环的入口点，空间复杂度O(1)
                快速节点和慢速节点必定在环的第二圈时相遇
	> Created Time: Wed 10 Oct 2018 09:07:12 AM CST
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
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if( pHead==NULL || pHead->next==NULL )
            return NULL;
        ListNode* fast = pHead, *low = pHead;
        do
        {
            fast = fast->next->next;
            low = low->next;
        }while( fast != low );
        fast = pHead;
        while( fast != low )
        {
            fast = fast->next;
            low = low->next;
        }
        return fast;
    }
};
