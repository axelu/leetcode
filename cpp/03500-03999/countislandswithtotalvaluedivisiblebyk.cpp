
// 3619. Count Islands With Total Value Divisible by K
// https://leetcode.com/problems/count-islands-with-total-value-divisible-by-k/



class Solution {
private:
    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    long explore(vector<vector<int>>& grid, int m, int n, int i, int j, vector<vector<bool>>& seen) {
        seen[i][j] = true;
        long ret = (long)grid[i][j];

        for(int k = 0; k < 4; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            if( seen[i_new][j_new] )
                continue;

            if( grid[i_new][j_new] == 0 )
                continue;

            ret += explore(grid, m, n, i_new, j_new, seen);
        }

        return ret;
    }

public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int ans = 0;

        vector<vector<bool>> seen(m, vector<bool>(n,false));
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( seen[i][j] || grid[i][j] == 0 )
                    continue;
                long sum = explore(grid, m, n, i, j, seen);
                if( sum % (long)k == 0 )
                    ++ans;
            }
        }

        return ans;
    }
};
