
// 19. Remove Nth Node From End of List
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/


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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        vector<ListNode*> v;
        ListNode* ln = head;
        while(ln != nullptr) {
            v.push_back(ln);
            ln = ln->next;
        }
        int vsz = v.size();

        if( vsz == 1 ) return nullptr;

        // idx of node to be removed
        int idx = vsz - n;

        if( idx == 0 ) {
            head = head->next;
            return head;
        }
        ListNode* predecessor = v[idx-1];
        if( n == 1 ) {
            predecessor->next = nullptr;
            return head;
        }
        ListNode* successor = v[idx+1];
        predecessor->next = successor;
        return head;
    }
};
