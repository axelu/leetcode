
// 3128. Right Triangles
// https://leetcode.com/problems/right-triangles/





class Solution {
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        if( m == 1 || n == 1 )
            return 0LL;

        // we will view the current cell in grid as the corner with the 90deg angle

        int cntR[m];memset(cntR,0,sizeof cntR); // count of 1s per row
        int cntC[n];memset(cntC,0,sizeof cntC); // count of 1s per col
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 ) {
                    ++cntR[i];
                    ++cntC[j];
                }

        long long ans = 0;

        int seenR[m];memset(seenR,0,sizeof seenR); // count of 1s per row
        int seenC[n];memset(seenC,0,sizeof seenC); // count of 1s per col
        // top to bottom, left to right
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 1 ) {

                    long long ones_above = seenC[j];
                    long long ones_below = cntC[j] - seenC[j] - 1;
                    long long ones_left  = seenR[i];
                    long long ones_right = cntR[i] - seenR[i] - 1;

                    if( i == 0 && j == 0 ) {                        // top left
                        ans += ones_below * ones_right;

                    } else if( i == 0 && j == n-1 ) {               // top right
                        ans += ones_below * ones_left;

                    } else if( i == 0 && j != 0 && j != n-1 ) {     // top row
                        ans += ones_below * ones_left;
                        ans += ones_below * ones_right;

                    } else if( i != 0 && i != m-1 && j == 0 ) {     // left column
                        ans += ones_above * ones_right;
                        ans += ones_below * ones_right;

                    } else if( i == m-1 && j == 0 ) {               // bottom left
                        ans += ones_above * ones_right;

                    } else if( i != 0 && i != m-1 && j == n-1 ) {   // right column
                        ans += ones_above * ones_left;
                        ans += ones_below * ones_left;

                    } else if( i == m-1 && j == n-1 ) {             // bottom right
                        ans += ones_above * ones_left;

                    } else if( i == m-1 && j != 0 && j != n-1 ) {   // bottom row
                        ans += ones_above * ones_left;
                        ans += ones_above * ones_right;

                    } else {
                        ans += ones_above * ones_left;
                        ans += ones_above * ones_right;
                        ans += ones_below * ones_left;
                        ans += ones_below * ones_right;
                    }

                    ++seenR[i];
                    ++seenC[j];
                }
            }
        }

        return ans;
    }
};
