
// 203. Romove Linked List Elements
// https://leetcode.com/problems/remove-linked-list-elements/


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
    ListNode* removeElements(ListNode* head, int val) {
        if ( head == nullptr ) return nullptr;
        
        ListNode* wn = head;
        ListNode* rn = head->next;
        while( rn != nullptr ) {
            
            if( rn->val == val ) {
                wn->next = nullptr;
            } else {
                wn->next = rn;
                wn = rn;
            }
            
            rn = rn->next;
        }
        
        // taking care of head itself
        return ( head->val == val ) ? ( head->next == nullptr ) ? nullptr : head->next : head;
    }
};
