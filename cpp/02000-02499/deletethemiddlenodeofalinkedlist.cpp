
// 2095. Delete the Middle Node of a Linked List
// https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/




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
    ListNode* deleteMiddle(ListNode* head) {
        if( head->next == nullptr )
            return nullptr;

        int c = 0;
        ListNode* n = head->next;
        ListNode* p = head;

        while( n != nullptr ) {
            ++c;
            if( c == 3 ) {
                p = p->next;
                c = 1;
            }
            n = n->next;
        }

        // p -> B -> C
        // B is to be be removed
        ListNode* C = p->next->next;
        p->next = C;

        return head;
    }
};
