
// 141. Linked List Cycle
// https://leetcode.com/problems/linked-list-cycle/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if ( head == nullptr ) return false;
        if ( head->next == nullptr ) return false;

        unordered_set<ListNode*> u;
        return explore(head, u);
    }
private:
    bool explore(ListNode* h, unordered_set<ListNode*>& u) {
        if ( h == nullptr ) return false;
        if ( !u.insert(h).second ) return true;
        return explore(h->next, u);
    }
};
