/*************************************************************************
	> File Name: A70.cpp
	> Author: zj
	> Describe: 删除排序链表中重复的节点
                1->2->3->3->4->4->5 处理后为 1->2->5
	> Created Time: Thu 11 Oct 2018 09:51:05 PM CST
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
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if( pHead == NULL )
            return pHead;
        ListNode* beg = NULL;
        ListNode* tmp = NULL;
        int last;
        while( pHead != NULL )
        {
            last = pHead->val;
            if( pHead->next != NULL && pHead->next->val == last )
            {
                while( pHead->next != NULL && pHead->next->val == last )
                    pHead->next = pHead->next->next;
                if( tmp != NULL )
                    tmp->next = pHead->next;
            }
            else
            {
                if( beg == NULL )
                    beg = pHead;
                tmp = pHead;
            }
            pHead = pHead->next;
        }
        return beg;
    }
};

int main()
{
    ListNode* first = new ListNode(1);
    first->next = new ListNode(2);
    first->next->next = new ListNode(3);
    first->next->next->next = new ListNode(3);
    first->next->next->next->next = new ListNode(4);
    ListNode* f = Solution().deleteDuplication(first);
    while( f!=NULL )
    {
        cout<<f->val<<" ";
        f = f->next;

    }
}
