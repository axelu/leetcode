
// 86. Partition List
// https://leetcode.com/problems/partition-list/
// day 14 April 2021 challenge
// https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3707/




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
    ListNode* partition(ListNode* head, int x) {
        if( head == nullptr ) return nullptr;
        if( head->next == nullptr ) return head;

        ListNode* prev = nullptr;
        ListNode* pred = nullptr;
        ListNode* next = nullptr;

        ListNode* node = head;
        while( node != nullptr ) {
            // cout << node->val << endl;
            if( node->val >= x && next == nullptr ) {
                // 1st node we encounter where val >= x
                next = node;
                pred = prev;
                prev = node;
                node = node->next;
                continue;
            }
            if( node->val < x && next != nullptr ) {
                // move the current node before next
                if( pred == nullptr ) {
                    // our node will become the new head!
                    head = node;
                } else {
                    pred->next = node;
                }
                prev->next = node->next;
                node->next = next;
                pred = node;
                node = prev->next;
                continue;
            }

            if( next == nullptr ) pred = node;
            prev = node;
            node = node->next;
        }
        return head;
    }
};
