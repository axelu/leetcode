
// 25. Reverse Nodes in k-Group
// https://leetcode.com/problems/reverse-nodes-in-k-group/
// day 18 July 2021 challenge
// https://leetcode.com/explore/featured/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3818/






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
    struct T{
        bool f;
        ListNode* head; // prev
        ListNode* next; // curr
    };

    T reverseLinkedList(ListNode* head, int k) {
        ListNode* curr = head;
        ListNode* prev = nullptr;
        int i = 0;

        while( curr != nullptr && i < k) {
            ++i;
            ListNode* t = curr->next;
            curr->next = prev;
            prev = curr;
            curr = t;
        }
        bool f = i < k ? false : true;
        // prev = new head
        // curr = next node

        return {f,prev,curr};
    }


public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if( k == 1 )
            return head;

        ListNode* newHead = nullptr;
        ListNode* prev = nullptr;

        while( true ) {

            T t = reverseLinkedList(head,k);
            if( newHead == nullptr )
                newHead = t.head;

            if( !t.f ) {
                t = reverseLinkedList(t.head,k);
                prev->next = t.head;
                break;
            }

            if( prev != nullptr )
                prev->next = t.head;
            prev = head;
            head = t.next;

            if( t.f && t.next == nullptr ) {
                break;
            }
        }

        return newHead;
    }
};
