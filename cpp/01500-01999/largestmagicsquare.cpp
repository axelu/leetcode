
// 1895. Largest Magic Square
// https://leetcode.com/problems/largest-magic-square/





class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        if( m == 1 || n == 1 )
            return 1;

        vector<vector<int>> prefixSum_row(m,vector<int>(n+1,0));
        for(int i = 0; i < m; ++i)          // row
            for(int j = 1; j <= n; ++j)     // col
                prefixSum_row[i][j] =  prefixSum_row[i][j-1] + grid[i][j-1];

        vector<vector<int>> prefixSum_col(m+1,vector<int>(n,0));
        for(int j = 0; j < n; ++j)          // col
            for(int i = 1; i <= m; ++i)     // row
                prefixSum_col[i][j] =  prefixSum_col[i-1][j] + grid[i-1][j];

        int ans = 1; // Every 1 x 1 grid is trivially a magic square.

        int i = 0;
        while( i < m - ans ) {
            int j = 0;
            while( j < n - ans ) {

                int k_max = min(m-i,n-j); // we will start with k as large as possible
                int k_min = ans + 1;      // we don't need to check k <= ans

                for(int k = k_max; k >= k_min; --k) {
                    bool f = true;

                    int sum = prefixSum_row[i][j+k] - prefixSum_row[i][j];

                    // row sums row[i,i+k-1] starting at col j and length k
                    for(int r = i+1; r < i+k; ++r)
                        if( prefixSum_row[r][j+k] - prefixSum_row[r][j] != sum ) {
                            f = false;
                            break;
                        }

                    // col sums col[j,j+k-1] starting at row i and length k
                    if( f ) {
                        for(int c = j; c < j+k; ++c)
                            if( prefixSum_col[i+k][c] - prefixSum_col[i][c] != sum ) {
                                f = false;
                                break;
                            }
                    }

                    // diagonal check left top to right bottom
                    if( f ) {
                        int sum_lt_rb = 0;
                        for(int r = i, c = j, t = 0; t < k; ++t, ++r, ++c)
                            sum_lt_rb += grid[r][c];
                        if( sum_lt_rb != sum )
                            f = false;
                    }

                    // diagonal check left bottom to right top
                    if( f ) {
                        int sum_lb_rt = 0;
                        for(int r = i, c = j+k-1, t = 0; t < k; ++t, ++r, --c)
                            sum_lb_rt += grid[r][c];
                        if( sum_lb_rt != sum )
                            f = false;
                    }

                    if( f ) {
                        ans = k;
                        break;
                    }
                }
                ++j;
            }
            ++i;
        }

        return ans;
    }
};
