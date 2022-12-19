
// 2373. Largest Local Values in a Matrix
// https://leetcode.com/problems/largest-local-values-in-a-matrix/



class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<vector<int>> ans(n-2,vector<int>(n-2));

        // brute force
        for(int i = 1; i < n-1; ++i) {      // row in grid
            int i_new = i-1;                // row in ans
            for(int j = 1; j < n-1; ++j) {  // col in grid
                int j_new = j-1;            // col in ans

                int mx = 0;
                for(int r = i-1; r <= i+1; ++r)
                    for(int c = j-1; c <= j+1; ++c)
                        mx = max(mx,grid[r][c]);

                ans[i_new][j_new] = mx;
            }
        }

        return ans;
    }
};
