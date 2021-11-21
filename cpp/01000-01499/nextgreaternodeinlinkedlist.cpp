
// 1019. Next Greater Node In Linked List
// https://leetcode.com/problems/next-greater-node-in-linked-list/




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
    vector<int> nextLargerNodes(ListNode* head) {
        if( head == nullptr )
            return {};
        if( head->next == nullptr )
            return {0};

        /*
        // solution with reversing the linked list 1st
        stack<int> park;
        while( head != nullptr ) {
            park.push(head->val);
            head = head->next;
        }
        // park now contains values of linked list in reverse

        int n = park.size();
        vector<int> ans(n);


        stack<int> stck; // monotonic stack
        int i = n-1,val;
        while( !park.empty() ) {
            val = park.top();
            park.pop();

            while( !stck.empty() && stck.top() <= val )
                stck.pop();

            if( !stck.empty() )
                ans[i] = stck.top();

            --i;
            stck.push(val);
        }

        return ans;
        */

        // solution w/o reversing the linked list

        vector<int> ans(10000); // we don't know how long the linked list is yet
                                // the given list has length in the range [0, 10000]

        stack<vector<int>> stck; // val,index
        int i = 0, val;

        while( head != nullptr ) {
            val = head->val;
            head = head->next;

            while( !stck.empty() && stck.top()[0] < val ) {
                ans[stck.top()[1]] = val;
                stck.pop();
            }

            stck.push({val,i});
            ++i;
        }

        // finish up
        while( !stck.empty() ) {
            ans[stck.top()[1]] = 0;
            stck.pop();
        }

        return vector<int>(ans.begin(),ans.begin()+i);
    }
};
