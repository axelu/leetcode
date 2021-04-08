
// Sort List
// day 13 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/560/week-2-october-8th-october-14th/3493/
// https://leetcode.com/problems/sort-list/


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
    multiset<int> s;
    void _walk(ListNode* head) {
        if( head == nullptr ) return;
        s.insert(head->val);
        _walk(head->next);
    }

public:
    ListNode* sortList(ListNode* head) {
        if( head == nullptr ) return nullptr;

        _walk(head);
        auto it = begin(s);
        head = new ListNode(*it);
        ListNode* parent = head;
        for(++it; it != end(s); ++it) {
            ListNode* ln = new ListNode(*it);
            parent->next = ln;
            parent = ln;
        }

        return head;
    }
};
