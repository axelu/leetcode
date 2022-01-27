
// 2130. Maximum Twin Sum of a Linked List
// https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/



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
    int pairSum(ListNode* head) {
        stack<ListNode*> stck;

        ListNode* n = head;
        while( n != nullptr ) {
            stck.push(n);
            n = n->next;
        }

        int mx = 0;

        n = head;
        while( stck.top()->next != n ) {
            mx = max(mx,n->val + stck.top()->val);
            n = n->next;
            stck.pop();
        }

        return mx;
    }
};
