
// 328. Odd Even Linked List
// https://leetcode.com/problems/odd-even-linked-list/




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
    ListNode* oddEvenList(ListNode* head) {
        if( head == nullptr || head->next == nullptr )
            return head;

        ListNode* lastOdd = head;
        ListNode* curr    = head->next;
        ListNode* prev    = head;
        ListNode* next;
        int mode = 0; // 0 even, 1 odd
        while( curr != nullptr ) {
            next = curr->next;
            if( mode == 1 ) { // odd node
                prev->next = next;

                curr->next = lastOdd->next;
                lastOdd->next = curr;
                lastOdd = curr;

                curr = next;
                mode = !mode;
                continue;
            }

            prev = curr;
            curr = next;

            mode = !mode;
        }

        return head;
    }
};
