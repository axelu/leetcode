
// 741. Cherry Pickup
// https://leetcode.com/problems/cherry-pickup/


class Solution {
private:
    size_t N;
    int mem[50][50][50];

    int dp(vector<vector<int>>& grid, int r1, int c1, int c2) {
        int r2 = r1 + c1 - c2; // row of picker 2

        if( r1 == N || N == r2 || N == c1 || N == c2 ||
                grid[r1][c1] == -1 || grid[r2][c2] == -1) {
            return INT_MIN;
        } else if( r1 == N-1 && c1 == N-1 ) {
            return grid[r1][c1];
        } else if( mem[r1][c1][c2] != INT_MIN ) {
            return mem[r1][c1][c2];
        } else {
            int ans = grid[r1][c1];
            if( c1 != c2 ) ans += grid[r2][c2]; // no double counting
            ans += max({dp(grid,r1, c1+1, c2+1),
                        dp(grid,r1+1, c1, c2+1),
                        dp(grid,r1, c1+1, c2),
                        dp(grid,r1+1, c1, c2)});
            return mem[r1][c1][c2] = ans;
        }
    }


public:
    int cherryPickup(vector<vector<int>>& grid) {
        N = grid.size(); // n == grid.length, n == grid[i].length
        if( N == 1 ) return grid[0][0];

        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                for(int k = 0; k < N; ++k)
                    mem[i][j][k] = INT_MIN;

        return max(0,dp(grid,0,0,0));
    }
};
