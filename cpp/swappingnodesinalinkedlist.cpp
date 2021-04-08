
// 1721. Swapping Nodes in a Linked List
// https://leetcode.com/problems/swapping-nodes-in-a-linked-list/

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
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* arr[100001];
        int i = 0;
        ListNode* ln = head;
        while(ln!=nullptr) {
            ++i;
            arr[i] = ln;
            ln = ln->next;
        }
        int idxfe = i+1-k;
        int t = (arr[k])->val;
        (arr[k])->val = (arr[idxfe])->val;
        (arr[idxfe])->val = t;
        return head;
    }
};
