
// 1474. Delete N Nodes After M Nodes of a Linked List
// https://leetcode.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/



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
    ListNode* deleteNodes(ListNode* head, int m, int n) {
        ListNode* prev;
        ListNode* ln = head;
        int i = 0;
        int j = n;
        while(ln!=nullptr) {
            if( j == n ) {
                ++i;
                if( i == m ) {
                    prev = ln;
                    j = 0;
                }
            } else if( i == m ) {
                ++j;
                if( j == n ) {
                    prev->next = ln->next;
                    i = 0;
                }
            }
            ln = ln->next;
        }
        if( j < n ) prev->next = nullptr;

        return head;
    }
};
