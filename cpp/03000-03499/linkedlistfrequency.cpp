
// 3063. Linked List Frequency
// https://leetcode.com/problems/linked-list-frequency/




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
    ListNode* frequenciesOfElements(ListNode* head) {

        unordered_map<int,int> freq; // val, count

        ListNode* ln = head;
        while( ln != nullptr ) {
            ++freq[ln->val];
            ln = ln->next;
        }

        ListNode* head_new = new ListNode(freq.begin()->second);
        ListNode* prev = head_new;
        for(auto it = next(freq.begin()); it != freq.end(); ++it) {
            ln = new ListNode(it->second);
            prev->next = ln;
            prev = ln;
        }

        return head_new;
    }
};
