
// 83. Remove Duplicates from Sorted List
// https://leetcode.com/problems/remove-duplicates-from-sorted-list/

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {

        // head is nullptr
        if ( head == nullptr ) return head;

        ListNode* wn = head;
        ListNode* rn = head->next;
        while( rn != nullptr ) {

            if( wn->val != rn->val ) {
                wn->next = rn;
                wn = rn;
                rn = wn->next;
            } else {
                wn->next = nullptr;
                rn = rn->next;
            }
        }

        return head;
    }
};
