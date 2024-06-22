
// 3142. Check if Grid Satisfies Conditions
// https://leetcode.com/problems/check-if-grid-satisfies-conditions/





class Solution {
public:
    bool satisfiesConditions(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( i + 1 < m ) {
                    // check cell below for equality
                    if( grid[i][j] != grid[i+1][j] )
                        return false;
                }
                if( j + 1 < n ) {
                    // check cell to the right for inequality
                    if( grid[i][j] == grid[i][j+1] )
                        return false;
                }
            }
        }

        return true;
    }
};
