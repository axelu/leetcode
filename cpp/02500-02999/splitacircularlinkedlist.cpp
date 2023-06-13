
// 2674. Split a Circular Linked List
// https://leetcode.com/problems/split-a-circular-linked-list/



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
    vector<ListNode*> splitCircularLinkedList(ListNode* list) {

        ListNode* head = list;
        ListNode* head2;

        ListNode* ln = list;
        ListNode* ln2 = list; // go around twice as fast

        while( true ) {
            // ln will be pointing to end of 1st half
            //   with that ln->next is pointing to begin of 2nd half
            // ln2 is pointing to end of 2nd half

            if( ln2->next == head ) {
                head2 = ln->next;
                ln->next = head;
                ln2->next = head2;
                break;
            }
            ln2 = ln2->next;

            if( ln2->next == head ) {
                head2 = ln->next;
                ln->next = head;
                ln2->next = head2;
                break;
            }
            ln2 = ln2->next;

            ln = ln->next;
        }

        return {head,head2};
    }
};
