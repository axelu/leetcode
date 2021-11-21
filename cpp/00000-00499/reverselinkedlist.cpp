
// 206. Reverse Linked List
// https://leetcode.com/problems/reverse-linked-list/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if( head == nullptr ) return head;
        if( head->next == nullptr ) return head;

        ListNode *p = nullptr;
        while( head != nullptr ) {
            ListNode *t = head->next;
            head->next = p;
            p = head;
            head = t;
        }

        return p;
    }
};
