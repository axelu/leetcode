
// 2639. Find the Width of Columns of a Grid
// https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/




class Solution {
public:
    vector<int> findColumnWidth(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        vector<int> ans(n);

        for(int j = 0; j < n; ++j) {
            int t = 1;

            for(int i = 0; i < m; ++i) {
                if( grid[i][j] == 0 )
                    continue;

                int w = grid[i][j] > 0 ? 0 : 1;
                int x = abs(grid[i][j]);
                while( x > 0 ) {
                    ++w;
                    x /= 10;
                }

                t = max(t,w);
            }
            ans[j] = t;
        }

        return ans;
    }
};
