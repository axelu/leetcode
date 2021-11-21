
// 54. Spiral Matrix
// https://leetcode.com/problems/spiral-matrix/


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        size_t m = matrix.size();   // rows
        size_t n = matrix[0].size();// columns

        vector<int> ans(m*n);

        // base cases
        if( m == 1 && n == 1) {
            ans[0] = matrix[0][0];
            return ans;
        }
        if( m == 1 ) { // one row only
            for(int j = 0; j < n; ++j) ans[j] = matrix[0][j];
            return ans;
        }
        if( n == 1 ) { // one column only
            for(int i = 0; i < m; ++i) ans[i] = matrix[i][0];
            return ans;
        }

        int dir = 0; // 0 right, 1 down, 2 left, 3 up
        int k = 0, i = 0, j = 0;
        int mnr = 0, mxr = m-1, mnc = 0, mxc = n-1;
        while(k < m*n) {

            // right
            if( 0 == dir ) {
                while(j <= mxc) {
                    //cout << "right " << i << " " << j << endl;
                    ans[k] = matrix[i][j];
                    ++k;
                    ++j;
                }
                dir = 1;
                --j; // reset
                ++i;
                ++mnr;
                continue;
            }

            // down
            if( 1 == dir ) {
                while(i <= mxr) {
                    //cout << "down  " << i << " " << j << endl;
                    ans[k] = matrix[i][j];
                    ++k;
                    ++i;
                }
                dir = 2;
                --i; // reset
                --j;
                --mxc;
                continue;
            }

             // left
            if( 2 == dir ) {
                while(j >= mnc) {
                    //cout << "left  " << i << " " << j << endl;
                    ans[k] = matrix[i][j];
                    ++k;
                    --j;
                }
                dir = 3;
                ++j; // reset
                --i;
                --mxr;
                continue;
            }

             // up
            if( 3 == dir ) {
                while(i >= mnr) {
                    //cout << "up    " << i << " " << j << endl;
                    ans[k] = matrix[i][j];
                    ++k;
                    --i;
                }
                dir = 0;
                ++i; // reset
                ++j;
                ++mnc;
                //continue;
            }
        }

        return ans;
    }
};
