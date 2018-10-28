/*************************************************************************
	> File Name: 52.cpp
	> Author: zj
	> Describe: 两个链表的第一个公共节点
                两个指针，一个先访问A，后访问B
                另一个先访问B，后访问A，交点就是公共节点
	> Created Time: Thu 11 Oct 2018 03:48:00 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x):val(x), next(NULL) {
	}
};
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode* p1 = pHead1, *p2 = pHead2;
        while( p1 != p2 )
        {
            p1 = (p1 == NULL) ? pHead2 : p1->next;
            p2 = (p2 == NULL) ? pHead1 : p2->next;
        }
        return p1;
    }
};

int main()
{
    ListNode* common = new ListNode(11);

    ListNode* a1 = new ListNode(1);
    a1->next = new ListNode(2);
    a1->next->next = common;

    ListNode* a2 = new ListNode(5);
    a2->next = new ListNode(2);
    a2->next->next = new ListNode(2);
    a2->next->next->next = common;

    Solution t;
    cout<<t.FindFirstCommonNode( a1, a2 )->val<<"\n";
}
