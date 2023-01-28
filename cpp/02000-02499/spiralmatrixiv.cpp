
// 2326. Spiral Matrix IV
// https://leetcode.com/problems/spiral-matrix-iv/




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
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> ans(m,vector<int>(n,-1));

        int i = 0;
        int j = 0;

        int mn_row = 0, mx_row = m-1;
        int mn_col = 0, mx_col = n-1;

        ListNode* nd = head;
        int dir = 0;
        while( nd != nullptr ) {
            ans[i][j] = nd->val;
            if( dir % 4 == 0 ) {       // right
                if( j == mx_col ) {
                    // change direction to down
                    dir = 1;
                    ++i;
                    mn_row = i;
                } else {
                    ++j;
                }
            } else if( dir % 4 == 1 ) { // down
                if( i == mx_row ) {
                    // change direction to left
                    dir = 2;
                    --j;
                    mx_col = j;
                } else {
                    ++i;
                }
            } else if( dir % 4 == 2 ) { // left
                if( j == mn_col ) {
                    // change direction to up
                    dir = 3;
                    --i;
                    mx_row = i;
                } else {
                    --j;
                }
            } else {                    // up
                if( i == mn_row ) {
                    // change direction to right
                    dir = 0;
                    ++j;
                    mn_col = j;
                } else {
                    --i;
                }
            }
            nd = nd->next;
        }

        return ans;
    }
};
