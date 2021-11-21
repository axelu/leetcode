
// 2046. Sort Linked List Already Sorted Using Absolute Values
// https://leetcode.com/problems/sort-linked-list-already-sorted-using-absolute-values/



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
    ListNode* remove(ListNode* prev) {
        ListNode* n = prev->next;
        ListNode* next = n->next;

        prev->next = next;
        return next;
    }

public:
    ListNode* sortLinkedList(ListNode* head) {
        if( head->next == nullptr )
            return head;

        ListNode* n = head;
        int val;
        ListNode* prev = nullptr;
        while( n != nullptr ) {
            val = n->val;

            if( n->next == nullptr && val < 0 ) {
                n->next = head;
                head = n;
                prev->next = nullptr;
                break;
            }

            // if n->val < 0
            //    remove the current node
            //    make the removed node the new head
            if( val < 0 && prev != nullptr) {
                ListNode* t = n;
                n = remove(prev);
                t->next = head;
                head = t;
                continue;
            }

            prev = n;
            n = n->next;
        }

        return head;
    }
};
