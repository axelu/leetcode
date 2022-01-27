
// 944. Delete Columns to Make Sorted
// https://leetcode.com/problems/delete-columns-to-make-sorted/


class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int m = strs.size();    // rows
        int n = strs[0].size(); // cols

        int ans = 0;
        for(int j = 0; j < n; ++j)        // cols
            for(int i = 1; i < m; ++i)    // rows
                if( strs[i][j] < strs[i-1][j] ) {
                    ++ans;
                    break;
                }
        return ans;
    }
};
