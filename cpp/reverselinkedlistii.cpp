
// 92. Reverse Linked List II
// https://leetcode.com/problems/reverse-linked-list-ii/




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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if( m == n ) return head;

        ListNode* ret = head;
        ListNode* prev = nullptr;
        ListNode* beforeFirst;
        ListNode* first;
        int k = 1;
        while( head != nullptr ) {
            if( k < m ) {
                prev = head;
                head = head->next;
            } else if( k == m ) {
                beforeFirst = prev;
                first = head;
                prev = head;
                head = head->next;
            } else if( k > m && k < n ) {
                ListNode* t = head->next;
                head->next = prev;
                prev = head;
                head = t;
            } else {
                // first time we get here is when k == n
                first->next = head->next;
                if( beforeFirst != nullptr ) beforeFirst->next = head;
                else ret = head;
                head->next = prev;
                break;
            }
            ++k;
        }
        return ret;
    }
};
