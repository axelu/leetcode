
// 2816. Double a Number Represented as a Linked List
// https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/




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
    ListNode* doubleIt(ListNode* head) {

        stack<ListNode*> stck;

        ListNode* ln = head;
        while( ln != nullptr ) {
            stck.push(ln);
            ln = ln->next;
        }

        int rem = 0;
        while( !stck.empty() ) {
            ln = stck.top();
            stck.pop();

            int val = (ln->val) * 2 + rem;
            ln->val = val % 10;
            rem = val / 10;
        }

        if( rem > 0 )
            head = new ListNode(rem,ln);

        return head;
    }
};
