
// 1139. largest 1-Bordered Square
// https://leetcode.com/problems/largest-1-bordered-square/



class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int ans = 0;

        int u[m][n];memset(u,0,sizeof u); // ones to the left
        int l[m][n];memset(l,0,sizeof l); // ones to the top

        int k;
        for(int r = 0; r < m; ++r) {
            for(int c = 0; c < n ; ++c) {

                if( grid[r][c] == 1 ) {
                    // 1s to the top
                    u[r][c] = r > 0 ? 1 + u[r-1][c] : 1;
                    // 1s to the left
                    l[r][c] = c > 0 ? 1 + l[r][c-1] : 1;

                    // our current cell is the bottom right corner of a sqare
                    k = min(u[r][c],l[r][c]);
                    for(; k * k > ans; --k) {

                        // left bottom corner
                        // [r][c-k+1]

                        // right top corner
                        // [r-k+1][c]

                        // do 1s from the left bottom corner up and
                        // from the right top corrner left meet?
                        if( u[r][c-k+1] >= k && l[r-k+1][c] >= k ) {
                            ans = max(ans,k*k);
                            break;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
