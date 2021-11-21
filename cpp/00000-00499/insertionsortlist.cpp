
// 147. Insertion Sort List
// day 2 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/564/week-1-november-1st-november-7th/3517/
// https://leetcode.com/problems/insertion-sort-list/



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
    ListNode* head;

    ListNode* go(ListNode* curr, ListNode* prev) {
        if( curr == nullptr ) return nullptr;

        if( prev != nullptr ) {
            if( curr->val < prev->val ) {
                prev->next = curr->next;
                return curr;
            }
        }

        ListNode* t = go(curr->next, curr);
        while( t != nullptr ) {
            if( t->val < curr->val ) {
                if( prev != nullptr ) {
                    return t;
                } else {
                    // top
                    head = t;
                    head->next = curr;
                    t = go(head, nullptr);
                }
            } else {
                t->next = curr->next;
                curr->next = t;
                t = go(curr->next, curr);
            }
        }
        return t;
    }
public:
    ListNode* insertionSortList(ListNode* head) {
        if( head == nullptr ) return head;
        if( head->next == nullptr ) return head;

        this->head = head;
        go(head,nullptr);

        return this->head;
    }
};
