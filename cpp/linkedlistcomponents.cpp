
// 817. Linked List Components
// https://leetcode.com/problems/linked-list-components/



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
    int numComponents(ListNode* head, vector<int>& G) {
        int ans = 0;
        sort(begin(G),end(G));
        int mode = 0;
        bool f;
        while( head != nullptr ) {
            f = binary_search(begin(G),end(G),head->val);
            if( f ) {
                if( mode == 0 )
                    mode = 1;
            } else {
                if( mode == 1 ) {
                    ++ans;
                    mode = 0;
                }
            }
            head = head->next;
        }
        // finish up
        if( mode == 1 ) ++ans;

        return ans;
    }
};
