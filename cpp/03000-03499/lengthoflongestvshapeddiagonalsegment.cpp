
// 3459. Length of Longest V-Shaped Diagonal Segment
// https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/






class Solution {
private:
    //              0  1  2  3
    // directions  UR DR DL UL
    int dirR[4] = {-1, 1, 1,-1};
    int dirC[4] = { 1, 1,-1,-1};

    int m, n;

    int ans;

    void rec(vector<vector<int>>& grid, int i, int j, int step, int dir, bool can_turn) {
        ans = max(ans, step);

        // step 2 3 4 5 6 7 ...
        // grid 2 0 2 0 2 0 ...
        // => even step = grid must be 2, odd step = grid must be 0

        // TODO
        // if we have been here before including same direction and same can_turn
        // at a higher step or same step, we don't need to pursue this!
        // but we couldnt even get here again with the constraints of only 1 turn

        int step_new = step + 1;
        int grid_new = step_new % 2 ? 0 : 2;

        // same direction
        int i_new = i + dirR[dir];
        int j_new = j + dirC[dir];
        if( i_new >= 0 && i_new < m && j_new >= 0 && j_new < n && grid[i_new][j_new] == grid_new )
            rec(grid, i_new, j_new, step_new, dir, can_turn);

        // can_turn ?
        if( can_turn ) {
            int dir_new = (dir + 1) % 4;
            i_new = i + dirR[dir_new];
            j_new = j + dirC[dir_new];
            if( i_new >= 0 && i_new < m && j_new >= 0 && j_new < n && grid[i_new][j_new] == grid_new )
                rec(grid, i_new, j_new, step_new, dir_new, false);
        }

        return;
    }

public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        m = grid.size(); // rows
        n = grid[0].size(); // cols

        ans = 0;

        // we can start from a 1 and go
        // diagonally to a 2
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 1 ) {
                    ans = max(ans, 1);
                    for(int k = 0; k < 4; ++k) {
                        int i_new = i + dirR[k];
                        if( i_new < 0 || i_new == m )
                            continue;
                        int j_new = j + dirC[k];
                        if( j_new < 0 || j_new == n )
                            continue;
                        if( grid[i_new][j_new] != 2 )
                            continue;

                        rec(grid, i_new, j_new, 2, k, true);
                    }
                }
            }
        }

        return ans;
    }
};
