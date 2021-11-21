
// 23. Merge K Sorted Lists
// https://leetcode.com/problems/merge-k-sorted-lists/
// day 24 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/582/week-4-january-22nd-january-28th/3615/


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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        size_t n = lists.size();
        if( n == 0 ) return nullptr;

        auto cmp = [](ListNode* l, ListNode* r) {
            return l->val > r->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp); // min heap

        // push the beginnig of each list into our priority queue
        for(int i = 0; i < n; ++i)
            if( lists[i] != nullptr ) pq.push(lists[i]);

        ListNode* ans = nullptr;
        ListNode* prev = nullptr;
        ListNode* pqe;

        // first element
        if( !pq.empty() ) {
            pqe = pq.top();
            pq.pop();
            prev = pqe;
            if( pqe->next != nullptr ) pq.push(pqe->next);
            // set the root of our return list
            ans = pqe;
        }

        while( !pq.empty() ) {
            pqe = pq.top();
            pq.pop();
            prev->next = pqe;
            prev = pqe;
            if( pqe->next != nullptr ) pq.push(pqe->next);
        }

        // last element
        if( prev != nullptr ) prev->next = nullptr;

        return ans;
    }
};
