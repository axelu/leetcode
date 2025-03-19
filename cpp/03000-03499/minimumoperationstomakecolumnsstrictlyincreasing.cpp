
// 3402. Minimum Operations to Make Columns Strictly Increasing
// https://leetcode.com/problems/minimum-operations-to-make-columns-strictly-increasing



class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int ans = 0;

        for(int j = 0; j < n; ++j) {
            int pre = -1;
            for(int i = 0; i < m; ++i) {
                if( grid[i][j] > pre ) {
                    pre = grid[i][j];
                    continue;
                }

                ans += pre - grid[i][j] + 1;
                ++pre;
            }
        }

        return ans;
    }
};
