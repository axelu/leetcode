
// 82. Remove Duplicates from Sorted List II
// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// day 5 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/579/week-1-january-1st-january-7th/3593/



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
    ListNode* deleteDuplicates(ListNode* head) {
        if( head == nullptr ) return nullptr;
        if( head->next == nullptr ) return head;

        ListNode* pr = nullptr;
        ListNode* rn = head;
        head = nullptr;
        int skip = -101;
        while( rn != nullptr ) {
            if( skip == rn->val ) {
                rn = rn->next;
                continue;
            }

            // peek ahead to determine if we keep this node
            if( rn->next == nullptr || rn->next->val != rn->val ) {
                // keep
                if( pr != nullptr ) {
                    pr->next = rn;
                } else {
                    head = rn;
                }
                pr = rn;
            } else {
                if( pr != nullptr ) pr->next = nullptr;
                skip = rn->val;
            }
            rn = rn->next;
        }

        return head;
    }
};
