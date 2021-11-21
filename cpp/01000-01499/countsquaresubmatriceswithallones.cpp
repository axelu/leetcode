
// 1277. Count Square Submatrices with All Ones
// https://leetcode.com/problems/count-square-submatrices-with-all-ones/



class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();    // rows
        int n = matrix[0].size(); // cols

        int ans = 0;

        int cnt[m][n];
        int i,j,k,t;
        for(i = 0; i < m; ++i) {
            t = 0; // sum per row
            for(j = 0; j < n; ++j) {
                t += matrix[i][j];
                if( i > 0 ) cnt[i][j] = t + cnt[i-1][j];
                else cnt[i][j] = t;
            }
        }

        // debug
        /*
        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j) {
                cout << cnt[i][j] << " ";
            }
            cout << endl;
        }
        */

        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j) {
                ans += matrix[i][j];
                for(k = 1; k < min(m-i,n-j); ++k) { // length-1 of side of square matrix
                    if( i == 0 && j == 0 ) {
                        t = cnt[i+k][j+k];
                    } else if( i == 0 ) {
                        t = cnt[i+k][j+k] - cnt[i+k][j-1];
                    } else if( j == 0 ) {
                        t = cnt[i+k][j+k] - cnt[i-1][j+k];
                    } else {
                        t = cnt[i+k][j+k] - cnt[i+k][j-1] - cnt[i-1][j+k] + cnt[i-1][j-1];
                    }
                    if( t == (k+1)*(k+1) ) ++ans;
                    else break;
                }
            }
        }

        return ans;
    }
};
