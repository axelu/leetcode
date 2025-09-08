
// 3665. Twisted Mirror Path Count
// https://leetcode.com/problems/twisted-mirror-path-count/


class Solution {
private:
    const long mod = 1000000007L;

    int m, n;

    long mem[500][500][2];

    long rec(vector<vector<int>>& grid, int i, int j, bool right) {
        // right == true means the prior move was right
        // right == false means the prior move was down
        if( i == m || j == n )
            return 0L;

        if( i == m-1 && j == n-1 )
            return 1L;

        if( mem[i][j][right] != -1L )
            return mem[i][j][right];

        long ret = 0L;

        if( grid[i][j] == 1 ) {
            if( right )
                ret = rec(grid, i+1, j, false);
            else
                ret = rec(grid, i, j+1, true);

        } else {
            // go right
            ret = rec(grid, i, j+1, true);
            // go down
            ret = (ret + rec(grid, i+1, j, false)) % mod;
        }

        return mem[i][j][right] = ret;
    }

public:
    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols

        memset(mem, -1, sizeof mem);
        return rec(grid, 0, 0, false);
    }
};

