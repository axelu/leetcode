
// 725. Split Linked List in Parts
// https://leetcode.com/problems/split-linked-list-in-parts/





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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> ans;

        if( head == nullptr ) {
            for(int i = 0; i < k; ++i)
                ans.push_back(nullptr);
            return ans;
        }

        if( k == 1 ) {
            ans.push_back(head);
            return ans;
        }

        int n = 0;
        ListNode* nd = head;
        while( nd != nullptr ) {
            ++n;
            nd = nd->next;
        }

        int c = n/k;
        int offset = n%k;

        if( c == 0 ) {
            int i = 0;
            nd = head;
            ListNode* t;
            for(; i < offset; ++i) {
                t = nd->next;
                nd->next = nullptr;
                ans.push_back(nd);
                nd = t;
            }
            for(; i < k; ++i)
                ans.push_back(nullptr);
            return ans;
        }


        int i = 0;
        nd = head;
        ListNode* t;
        for(; i < offset; ++i) {
            for(int j = 0; j < c; ++j)
                nd = nd->next;
            t = nd->next;
            nd->next = nullptr;
            ans.push_back(head);
            head = t;
            nd = head;
        }
        for(; i < k; ++i) {
            for(int j = 0; j < c-1; ++j)
                nd = nd->next;
            t = nd->next;
            nd->next = nullptr;
            ans.push_back(head);
            head = t;
            nd = head;
        }
        return ans;
    }
};
