
// 1290. Convert Binary Number in a Linked List to Integer
// day 1 November 2020 challenge
// https://leetcode.com/explore/featured/card/november-leetcoding-challenge/564/week-1-november-1st-november-7th/3516/
// https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/


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
    int r;
    int go(ListNode* head) {
        if( head == nullptr ) return 0;;
        int i = go(head->next);
        r |= (head->val << i);
        return i + 1;
    }
public:
    int getDecimalValue(ListNode* head) {
        r = 0;

        go(head);

        return r;
    }
};
