
// 2328. Number of Increasing Paths in a Grid
// https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/



class Solution {
private:
    long mod = 1000000007;

    int m,n;
    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    long dfs(vector<vector<int>>& grid, int u, long seen[]) {

        if( seen[u] != -1L )
            return seen[u];

        // we only come here from a cell that is smaller
        // as the requirement is strictly increasing, we
        // wouldn't go back to it naturally

        int i = u / n;
        int j = u % n;

        long ret = 0;

        // explore all four directions
        for(int k = 0; k < 4; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            if( grid[i_new][j_new] <= grid[i][j] )
                continue;

            int v = i_new * n + j_new;
            ret = (ret + dfs(grid,v,seen)) % mod;
        }

        return seen[u] = (ret + 1) % mod;
    }

public:
    int countPaths(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols

        int grid_sz = m*n;
        long seen[grid_sz];
        for(int i = 0; i < grid_sz; ++i)
            seen[i] = -1;

        long ans = 0;

        for(int i = 0; i < grid_sz; ++i) {
            if( seen[i] == -1L )
                ans = (ans + dfs(grid,i,seen)) % mod;
            else
                ans = (ans + seen[i]) % mod;
        }

        return ans;
    }
};
