
// 3217. Delete Nodes From Linked List Present in Array
// https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/






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

    ListNode* del(ListNode* pre, ListNode* nd) {

        if( pre == nullptr ) {
            // nd must be head
            this->head = nd->next;
            nd = nd->next;

        } else if( nd->next == nullptr ) {
            pre->next = nullptr;
            nd = nullptr;

        } else {
            pre->next = nd->next;
            nd = nd->next;
        }

        return nd;
    }

public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        this->head = head;

        sort(nums.begin(), nums.end());
        ListNode* pre = nullptr;
        ListNode* nd = head;
        while( nd != nullptr ) {
            if( binary_search(nums.begin(), nums.end(), nd->val) ) {
                // pre remains pre
                // next becomes nd
                nd = del(pre, nd);
            } else {
                pre = nd;
                nd = nd->next;
            }
        }

        return this->head;
    }
};
