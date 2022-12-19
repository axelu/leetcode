
// 2500. Delete Greatest Value in Each Row
// https://leetcode.com/problems/delete-greatest-value-in-each-row/



class Solution {
public:
    int deleteGreatestValue(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        for(int i = 0; i < m; ++i)
            sort(grid[i].begin(),grid[i].end(),greater<int>());

        int ans = 0;

        for(int j = 0; j < n; ++j) {
            int mx = 0;
            for(int i = 0; i < m; ++i)
                mx = max(mx,grid[i][j]);
            ans += mx;
        }

        return ans;
    }
};
