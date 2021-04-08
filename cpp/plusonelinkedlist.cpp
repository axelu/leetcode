
// 369. Plus One Linked List
// https://leetcode.com/problems/plus-one-linked-list/


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
private:
    int rec(ListNode* ln) {
        if( ln == nullptr ) return 1;
        int rem = 0;
        int newVal = ln->val + rec(ln->next);
        if( newVal > 9 ) {
            rem = 1;
            newVal = 0;
        }
        ln->val = newVal;
        return rem;
    }
public:
    ListNode* plusOne(ListNode* head) {
        return rec(head) == 1 ? new ListNode(1,head) : head;
    }
};
