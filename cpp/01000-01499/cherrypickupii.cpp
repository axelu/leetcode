
// 1463. Cherry Pickup II
// https://leetcode.com/problems/cherry-pickup-ii/
// day 19 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/571/week-3-december-15th-december-21st/3571/



class Solution {
private:
    size_t N,M;
    int mem[70][70][70];

    int dp(vector<vector<int>>& grid, int row, int col1, int col2) {
        // row,col1 = location of robot1
        // row,col2 = loaction of robot2

        // we cannot go outside the grid
        if( col1 < 0 || col1 >=M || col2 < 0 || col2 >=M )
            return INT_MIN;

        // last row
        if( row == N-1 )
            return col1 == col2 ? grid[row][col1] : grid[row][col1]+grid[row][col2];

        // already answered
        if( mem[row][col1][col2] != INT_MIN )
            return mem[row][col1][col2];

        int ans = grid[row][col1];
        if( col1 != col2 ) ans += grid[row][col2];  // no double counting
        ans += max({dp(grid,row+1,col1-1,col2-1),   // robot1  left down; robot2  left down
                    dp(grid,row+1,col1-1,col2),     // robot1  left down; robot2       down
                    dp(grid,row+1,col1-1,col2+1),   // robot1  left down; robot2 right down
                    dp(grid,row+1,col1,col2-1),     // robot1       down; robot2  left down
                    dp(grid,row+1,col1,col2),       // robot1       down; robot2       down
                    dp(grid,row+1,col1,col2+1),     // robot1       down; robot2 right down
                    dp(grid,row+1,col1+1,col2-1),   // robot1 right down; robot2  left down
                    dp(grid,row+1,col1+1,col2),     // robot1 right down; robot2       down
                    dp(grid,row+1,col1+1,col2+1)}); // robot1 right down; robot2 right down
        return mem[row][col1][col2] = ans;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        N = grid.size();    // rows
        M = grid[0].size(); // columns

        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
                for(int k = 0; k < M; ++k)
                    mem[i][j][k] = INT_MIN;

        return dp(grid,0,0,M-1);
    }
};
