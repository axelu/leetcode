
// 237. Delete Node in a Linked List
// https://leetcode.com/problems/delete-node-in-a-linked-list/


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
    void deleteNode(ListNode* node) {
        if( node == nullptr ) return;

        if( node->next != nullptr ) {
            node->val = node->next->val;
            if( node->next->next == nullptr ) {
                ListNode* t = node->next;
                node->next = nullptr;
                deleteNode(t);
            } else {
                deleteNode(node->next);
            }
        } else {
            delete (node);
        }
    }
};
