
// 1504. Count Submatrices With All Ones
// https://leetcode.com/problems/count-submatrices-with-all-ones/



class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();     // rows
        int n = mat[0].size();  // cols

        int heights[m][n];memset(heights,0,sizeof heights);

        int ans = 0;

        for(int i = 0; i < m; ++i) {        // row

            for(int j = 0; j < n; ++j) {    // col
                // height of current col
                if( mat[i][j] == 0 ) {
                    heights[i][j] = 0;
                } else {
                    heights[i][j] = i > 0 ? heights[i-1][j]+1 : 1;
                    ans += heights[i][j];

                    // how many submatrices of all 1s end in current cell?
                    // 'end' here means current cell is bottom right corner
                    // of such submatrices
                    if( j > 0 ) {
                        int mn = heights[i][j];
                        for(int k = j-1; k >= 0; --k) {
                            mn = min(mn,heights[i][k]);
                            if( mn == 0 )
                                break;
                            ans += mn;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
