
// 3239. Minimum Number of Flips to Make Binary Grid Palindromic I
// https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-i/


class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // 1 <= m * n <= 2 * 1e5

        /*
        // try rows
        int ans_rows = 0;
        for(int r = 0; r < m; ++r) {
            int i = 0;
            int j = n-1;
            while( i < j ) {
                if( grid[r][i] != grid[r][j] )
                   ++ans_rows;
                ++i;
                --j;
            }
        }
        // try cols
        int ans_cols = 0;
        for(int c = 0; c < n; ++c) {
            int i = 0;
            int j = m-1;
            while( i < j ) {
                if( grid[i][c] != grid[j][c] )
                   ++ans_cols; 
                ++i;
                --j;
            }
        }
        
        return min(ans_rows, ans_cols);
        */
        
        
        int ans_rows = 0;
        int ans_cols = 0;
        for(int rt = 0, rb = m-1; rt <= rb; ++rt, --rb) {
        
            for(int cl = 0, cr = n-1; cl <= cr; ++cl, --cr) {
                // ans_rows
                if( grid[rt][cl] != grid[rt][cr] )
                    ++ans_rows;
                // don't double count if odd row count
                if( rt != rb )
                    if( grid[rb][cl] != grid[rb][cr] )
                        ++ans_rows;
                
                // ans_cols
                if( grid[rt][cl] != grid[rb][cl] )
                    ++ans_cols;
                // don't double count if odd col count
                if( cl != cr )
                if( grid[rt][cr] != grid[rb][cr] )
                    ++ans_cols;
            }
        }

        return min(ans_rows, ans_cols);
    }
};
