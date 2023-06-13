
// 840. Magic Squares In Grid
// https://leetcode.com/problems/magic-squares-in-grid/



class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int ans = 0;

        int prefixSumRow[m][n+1];memset(prefixSumRow,0,sizeof prefixSumRow);
        for(int i = 0; i < m; ++i)
            for(int j = 1; j <= n; ++j)
                prefixSumRow[i][j] = prefixSumRow[i][j-1] + grid[i][j-1];

        int prefixSumCol[n][m+1];memset(prefixSumCol,0,sizeof prefixSumCol);
        for(int j = 0; j < n; ++j)
            for(int i = 1; i <= m; ++i)
                prefixSumCol[j][i] = prefixSumCol[j][i-1] + grid[i-1][j];

        for(int i = 0; i <= m-3; ++i) {     // row
            for(int j = 0; j <= n-3; ++j) { // col
                //cout << "row " << i << " col " << j << endl;

                // row sum check
                int rs_a = prefixSumRow[i][j+3] - prefixSumRow[i][j];
                //cout << "rs_a " << rs_a << endl;
                int rs_b = prefixSumRow[i+1][j+3] - prefixSumRow[i+1][j];
                //cout << "rs_b " << rs_b << endl;
                if( rs_a != rs_b )
                    continue;
                int rs_c = prefixSumRow[i+2][j+3] - prefixSumRow[i+2][j];
                //cout << "rs_c " << rs_c << endl;
                if( rs_a != rs_c )
                    continue;

                // col sum check
                int cs_a = prefixSumCol[j][i+3] - prefixSumCol[j][i];
                //cout << "cs_a " << cs_a << endl;
                if( rs_a != cs_a )
                    continue;
                int cs_b = prefixSumCol[j+1][i+3] - prefixSumCol[j+1][i];
                //cout << "cs_b " << cs_b << endl;
                if( rs_a != cs_b )
                    continue;
                int cs_c = prefixSumCol[j+2][i+3] - prefixSumCol[j+2][i];
                //cout << "cs_c " << cs_c << endl;
                if( rs_a != cs_c )
                    continue;

                // unique check
                int unique[16];memset(unique,0,sizeof unique);
                bool all_unique = true;
                for(int r = i; r < i+3; ++r) {
                    for(int c = j; c < j+3; ++c) {
                        ++unique[grid[r][c]];
                        if( unique[grid[r][c]] > 1 ) {
                            all_unique = false;
                            break;
                        }
                    }
                    if( !all_unique )
                        break;
                }
                if( !all_unique )
                    continue;
                //cout << "all_unique" << endl;

                // 1-9?
                bool onethroughnine = true;
                for(int k = 1; k <= 9; ++k)
                    if( unique[k] == 0 ) {
                        onethroughnine = false;
                        break;
                    }
                if( !onethroughnine )
                    continue;
                // cout << "1-9" << endl;

                // diagonal check
                // bottom left -> top right
                int ds = 0;
                for(int r = i+2, c = j; r >= i; --r, ++c) {
                    ds += grid[r][c];
                }
                //cout << "bottom left -> top right " << ds << endl;
                if( rs_a != ds )
                    continue;
                //cout << "diagonal check bottom left -> top right" << endl;
                // top left -> bottom right
                ds = 0;
                for(int r = i, c = j; r <= i+2; ++r, ++c) {
                    ds += grid[r][c];
                }
                //cout << "top left -> bottom right " << ds << endl;
                if( rs_a != ds )
                    continue;
                //cout << "diagonal check top left -> bottom right" << endl;

                ++ans;
            }
        }

        return ans;
    }
};
