
// 2257. Count Unguarded Cells in the Grid
// https://leetcode.com/problems/count-unguarded-cells-in-the-grid/




class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<int>> grid(m,vector<int>(n,0));
        int ans = m*n;

        int walls_sz = walls.size();
        ans -= walls_sz;
        for(int i = 0; i < walls_sz; ++i)
            grid[walls[i][0]][walls[i][1]] = 1;

        int guards_sz = guards.size();
        for(int i = 0; i < guards.size(); ++i) {
            int gr = guards[i][0];
            int gc = guards[i][1];
            if( grid[gr][gc] == 0 ) // no wall, no guard, not covered
                --ans;
            grid[gr][gc] = 2;

            // right (horizontal)
            for(int c = gc+1; c < n; ++c) {
                if( grid[gr][c] == 3 ) // cell already covered horizontally
                    break;
                if( grid[gr][c] == 1 ) // wall
                    break;
                if( grid[gr][c] == 2 ) // guard
                    break;
                if( grid[gr][c] == 4 ) // cell already covered vertically
                    continue;
                --ans;
                grid[gr][c] = 3;
            }

            // down (vertical)
            for(int r = gr+1; r < m; ++r) {
                if( grid[r][gc] == 4 ) // cell already covered vertically
                    break;
                if( grid[r][gc] == 1 ) // wall
                    break;
                if( grid[r][gc] == 2 ) // guard
                    break;
                if( grid[r][gc] == 3 ) // cell already covered horizontally
                    continue;
                --ans;
                grid[r][gc] = 4;
            }

            // left (horizontal)
            for(int c = gc-1; c >= 0; --c) {
                if( grid[gr][c] == 3 ) // cell already covered horizontally
                    break;
                if( grid[gr][c] == 1 ) // wall
                    break;
                if( grid[gr][c] == 2 ) // guard
                    break;
                if( grid[gr][c] == 4 ) // cell already covered vertically
                    continue;
                --ans;
                grid[gr][c] = 3;
            }

            // up (vertical)
            for(int r = gr-1; r >= 0; --r) {
                if( grid[r][gc] == 4 ) // cell already covered vertically
                    break;
                if( grid[r][gc] == 1 ) // wall
                    break;
                if( grid[r][gc] == 2 ) // guard
                    break;
                if( grid[r][gc] == 3 ) // cell already covered horizontally
                    continue;
                --ans;
                grid[r][gc] = 4;
            }

        }

        return ans;
    }
};
