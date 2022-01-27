
// 876. Middle of the Linked List
// https://leetcode.com/problems/middle-of-the-linked-list/



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
    ListNode* middleNode(ListNode* head) {
        ListNode* ans = head;

        int i = 1;
        while(head != nullptr) {
            if( i % 2 == 0 ) ans = ans->next;
            head = head->next;
            ++i;
        }

        return ans;
    }
};
