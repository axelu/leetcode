
// 3286. Find a Safe Walk Through a Grid
// https://leetcode.com/problems/find-a-safe-walk-through-a-grid/


class Solution {
private:
    // directions  R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    int seen[50][50];

    bool rec(vector<vector<int>>& grid, int m, int n, int i, int j) {
        int health = seen[i][j];
        if( i == m-1 && j == n-1 )
            return true;

        // explore directions
        for(int k = 0; k < 4; ++k) {
            int i_new = i + dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            int health_new = health - grid[i_new][j_new];
            if( health_new == 0 )
                continue;

            if( health_new <= seen[i_new][j_new] )
                continue;

            seen[i_new][j_new] = health_new;
            if( rec(grid, m, n, i_new, j_new) )
                return true;
        }

        return false;
    }


public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        // we are going from [0,0] to [m-1,n-1]
        memset(seen,-1,sizeof seen);
        seen[0][0] = health - grid[0][0];
        return rec(grid, m, n, 0, 0);
    }
};
