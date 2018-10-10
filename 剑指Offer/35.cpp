/*************************************************************************
	> File Name: 35.cpp
	> Author: zj
	> Describe: 复杂链表的复制
	> Created Time: Wed 10 Oct 2018 02:47:08 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if( pHead == NULL )
            return NULL;
        RandomListNode* cur = pHead;
        // insert clone node after each node
        while( cur != NULL )
        {
            RandomListNode * clone = new RandomListNode(cur->label);
            clone->next = cur->next;
            cur->next = clone;
            cur = clone->next;
        }

        // build random connect
        cur = pHead;
        while( cur != NULL )
        {
            if( cur->random != NULL )
                cur->next->random = cur->random->next;
            cur = cur->next->next;
        }

        // seperate clone node from src data
        cur = pHead;
        RandomListNode* ret = pHead->next;
        while( cur->next != NULL )
        {
            RandomListNode* next = cur->next;
            cur->next = next->next;
            cur = next;
        }

        return ret;
    }
};
