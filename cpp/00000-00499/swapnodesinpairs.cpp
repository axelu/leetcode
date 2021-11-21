
// 24. Swap Nodes in Pairs
// https://leetcode.com/problems/swap-nodes-in-pairs/
// day 24 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3579/

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
    ListNode* swapPairs(ListNode* head) {
        if( head == nullptr || head->next == nullptr ) return head;

        stack<ListNode*> stck;
        while( head != nullptr ) {
            stck.push(head);
            head = head->next;
        }

        ListNode* current;
        if( stck.size() % 2 == 1 ) {
            // uneven number of nodes in list
            current = stck.top();
            stck.pop();
        } else {
            // even number of nodes in list
            current = nullptr;
        }

        ListNode* node1;
        ListNode* node2;
        while( !stck.empty() ) {
            node2 = stck.top();
            stck.pop();
            node1 = stck.top();
            stck.pop();
            node1->next = current;
            node2->next = node1;
            current = node2;
        }

        return current;
    }
};
