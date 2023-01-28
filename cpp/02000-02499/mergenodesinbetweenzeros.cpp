
// 2181. Merge Nodes in Between Zeros
// https://leetcode.com/problems/merge-nodes-in-between-zeros/



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
    ListNode* mergeNodes(ListNode* head) {

        ListNode* nd = head->next;

        ListNode* ans  = nullptr;
        ListNode* tail = nullptr;
        int sum = 0;

        while( nd != nullptr ) {
            sum += nd->val;
            if( nd-> val == 0 ) {
                ListNode* t = new ListNode(sum);
                if( tail == nullptr )
                    ans = t;
                else
                    tail->next = t;
                tail = t;
                sum = 0;
            }
            nd = nd->next;
        }

        return ans;
    }
};
