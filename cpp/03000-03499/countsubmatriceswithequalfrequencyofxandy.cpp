
// 3212. Count Submatrices With Equal Frequency of X and Y
// https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/





class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int ans = 0;

        // treat X = 1 and Y = -1, if equal count their sum is 0

        int x = -1; // smallest column where an x exists
        int sum[n];memset(sum,0,sizeof sum);
        for(int i = 0; i < m; ++i) {        // row
            int row = 0;
            for(int j = 0; j < n; ++j) {    // col
                if( grid[i][j] == 'X' ) {
                    if( x == -1 || x > j )
                        x = j;
                }

                if( grid[i][j] == 'X' )
                    row += 1;
                else if( grid[i][j] == 'Y' )
                    row -= 1;
                sum[j] += row;
                if( x != -1 && j >= x && sum[j] == 0 )
                    ++ans;
            }
        }

        return ans;
    }
};
