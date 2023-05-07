
// 2058. Find the Minimum and Maximum Number of Nodes Between Critical Points
// https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/



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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {

        int fst = -1;
        int lst = -1;
        int mn_dist = 1000001;

        ListNode * nd = head->next;
        int prev_val = head->val;
        int i = 1;
        while( nd != nullptr ) {
            if( nd->next != nullptr ) {
                if( (prev_val < nd->val && nd->val > nd->next->val) ||
                    (prev_val > nd->val && nd->val < nd->next->val) ) {

                    if( fst == -1 ) {
                        fst = i;
                        lst = i;
                    } else {
                        mn_dist = min(mn_dist,i - lst);
                        lst = i;
                    }
                }
            }

            prev_val = nd->val;
            nd = nd->next;
            ++i;
        }

        if( fst == -1 || fst == lst )
            return {-1,-1};

        return {mn_dist,lst-fst};
    }
};
