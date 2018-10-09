/*************************************************************************
	> File Name: 6.cpp
	> Author: zj
	> Describe: 从尾到头返回链表
	> Created Time: Tue 09 Oct 2018 10:30:19 AM CST
 ************************************************************************/

#include <iostream>
#include <vector>
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
    // 使用头插法
    vector<int> printListFromTailToHead(ListNode* head) {
        ListNode tmpHead(0);
        while( head != NULL )
        {
            ListNode* next = head->next;
            head->next = tmpHead.next;
            tmpHead.next = head;
            head = next;
        }
        head = tmpHead.next;
        vector<int> ret;
        while( head != NULL )
        {
            ret.push_back( head->val );
            head = head->next;
        }
        return ret;
    }
};
