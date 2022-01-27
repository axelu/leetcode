
// 2128. Remove All Ones With Row and Column Flips
// https://leetcode.com/problems/remove-all-ones-with-row-and-column-flips/



class Solution {
public:
    bool removeOnes(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // start from a grid with all 0s and
        // try to create grid

        int rowFlip[m];memset(rowFlip,0,sizeof rowFlip);
        // assume we are flipping col 0
        for(int i = 0; i < m; ++i)
            if( !grid[i][0] )
                rowFlip[i] = 1;

        // now we check if each col 1 to n-1
        // would match if we don't flip that column or
        // if we flip that column
        for(int j = 1; j < n; ++j) {
            bool f = true;
            // check if we don't flip this col
            for(int i = 0; i < m; ++i)
                if( rowFlip[i] != grid[i][j] ) {
                    f = false;
                    break;
                }
            if( !f ) {
                // check if we flip this col
                for(int i = 0; i < m; ++i)
                    if( rowFlip[i] == grid[i][j] ) {
                        return false;
                    }
            }
        }
        return true;
    }
};
