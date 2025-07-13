
// 3565. Sequential Grid Path Cover
// https://leetcode.com/problems/sequential-grid-path-cover/




class Solution {
private:
    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    int m, n, mn;
    long all_visited;
    vector<vector<int>> path;

    int rec(vector<vector<int>>& grid, int i, int j, int next, long mask, int k) {
        // cout << "rec i " << i << " j " << j << " next " << next << endl;
        // it is guaranteed that grid[i][j] is valid at this step

        int idx = i * n + j;
        long mask_new = mask | (1L<<idx); // mark current cell as visited
        path.push_back({i,j});            // add current cell to path

        if( mask_new == all_visited ) {
            // we have visited all cells
            return 1;
        }

        // TODO we could capture the state mask, next
        // and if we have been here before, then we don't need to go again


        // explore all 4 directions
        for(int dir = 0; dir < 4; ++dir) {
            int i_new = i + dirR[dir];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[dir];
            if( j_new < 0 || j_new == n )
                continue;

            int idx_new = i_new * n + j_new;
            if( mask_new & (1L<<idx_new) )
                continue;

            int next_new = next;
            if( grid[i_new][j_new] != 0 ) {
                if( grid[i_new][j_new] != next )
                    continue;
                else
                    ++next_new;
            }

            if( rec(grid, i_new, j_new, next_new, mask_new, k) )
                return 1;
        }

        // backtrack
        path.pop_back();
        return 0;
    }

public:
    vector<vector<int>> findPath(vector<vector<int>>& grid, int k) {
        m = grid.size();    // 1 <= m == grid.length <= 6
        n = grid[0].size(); // 1 <= n == grid[i].length <= 6
        mn = m * n;

        all_visited = pow(2,mn)-1L; // cout << "all_visited " << all_visited << endl;

        // we can start at any cell that is a 0 or a 1
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 0 ) {
                    int res = rec(grid, i, j, 1, 0L, k);
                    if( res )
                        return path;
                } else if( grid[i][j] == 1 ) {
                    int res = rec(grid, i, j, 2, 0L, k);
                    if( res )
                        return path;
                }
            }
        }

        return {};
    }
};
