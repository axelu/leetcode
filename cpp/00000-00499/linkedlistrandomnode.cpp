
// 382. Linked List Random Node
// https://leetcode.com/problems/linked-list-random-node/
// day 2 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/569/week-1-december-1st-december-7th/3552/


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
    vector<ListNode*> v;
    size_t n;

public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        ListNode* ln = head;
        while(ln != nullptr) {
            v.push_back(ln);
            ln = ln->next;
        }
        n = v.size();
        srand(time(nullptr));
    }

    /** Returns a random node's value. */
    int getRandom() {
        int rdm = rand() % n; // random in the range of 0 to n-1
        return v[rdm]->val;
    }
};
