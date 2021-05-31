
// 1314. Matrix Block Sum
// https://leetcode.com/problems/matrix-block-sum/



class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int m = mat.size();    // rows
        int n = mat[0].size(); // cols

        int i,j;

        // 2D prefix sum
        int ps[m][n];
        ps[0][0] = mat[0][0];
        // row 0
        for(j = 1; j < n; ++j)
            ps[0][j] = ps[0][j-1] + mat[0][j];
        // column 0
        for(i = 1; i < m; ++i)
            ps[i][0] = ps[i-1][0] + mat[i][0];

        for(i = 1; i < m; ++i)     // row
            for(j = 1; j < n; ++j) // col
                ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + mat[i][j];


        vector<vector<int>> ans(m,vector<int>(n));
        int rs,re,cs,ce,sum;
        for(i = 0; i < m; ++i) {     // row
            for(j = 0; j < n; ++j) { // col

                // top row
                rs = i-k >= 0 ? i-k : 0;
                // bottom row
                re = i+k <= m-1 ? i+k : m-1;

                // left column
                cs = j-k >= 0 ? j-k : 0;
                // right column
                ce = j+k <= n-1 ? j+k : n-1;

                if( rs == 0 && cs == 0 ) {
                    sum = ps[re][ce];
                } else if( rs == 0 ) {
                    sum = ps[re][ce] - ps[re][cs-1];
                } else if( cs == 0 ) {
                    sum = ps[re][ce] - ps[rs-1][ce];
                } else {
                    sum = ps[re][ce] - ps[re][cs-1] - ps[rs-1][ce] + ps[rs-1][cs-1];
                }

                ans[i][j] = sum;
            }
        }

        return ans;
    }
};
