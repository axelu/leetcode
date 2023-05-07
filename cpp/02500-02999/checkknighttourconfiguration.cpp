
// 2596. Check Knight Tour Configuration
// https://leetcode.com/problems/check-knight-tour-configuration/



class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size(); // grid.length == grid[i].length

        int moves[n*n][2];

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                moves[grid[i][j]][0] = i;
                moves[grid[i][j]][1] = j;
            }
        }

        if( moves[0][0] != 0 || moves[0][1] != 0 )
            return false;

        int pre_i = 0;
        int pre_j = 0;
        for(int k = 1; k < n*n; ++k) {
            int cur_i = moves[k][0];
            int cur_j = moves[k][1];

            bool f = false;

            if( cur_j == pre_j - 2 && ( cur_i == pre_i + 1 || cur_i == pre_i - 1) )
                f = true;

            if( !f ) {
                if( cur_j == pre_j - 1 && ( cur_i == pre_i + 2 || cur_i == pre_i - 2) )
                    f = true;
            }

            if( !f ) {
                if( cur_j == pre_j + 1 && ( cur_i == pre_i + 2 || cur_i == pre_i - 2) )
                    f = true;
            }

            if( !f ) {
                if( cur_j == pre_j + 2 && ( cur_i == pre_i + 1 || cur_i == pre_i - 1) )
                    f = true;
            }

            if( !f )
                return false;

            pre_i = cur_i;
            pre_j = cur_j;
        }

        return true;
    }
};
