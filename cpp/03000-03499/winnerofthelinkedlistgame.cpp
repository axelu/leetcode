
// 3062. Winner of the Linked List Game
// https://leetcode.com/problems/winner-of-the-linked-list-game/




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
    string gameResult(ListNode* head) {
        // number of nodes in the list is even

        int even = 0;
        int odd = 0;

        ListNode* ln = head;
        while( ln != nullptr ) {
            // current node == ln is even node
            int even_val = ln->val;
            int odd_val = ln->next->val;

            if( odd_val > even_val )
                ++odd;
            else if( even_val > odd_val )
                ++even;

            ln = ln->next->next;
        }

        if( even > odd )
            return "Even";
        else if( odd > even )
            return "Odd";
        else
            return "Tie";
    }
};
