
// 566. Reshape the Matrix
// https://leetcode.com/problems/reshape-the-matrix/



class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        int m = nums.size();    // rows of the original matrix
        int n = nums[0].size(); // cols of the original matrix
        if( m*n != r*c ) return nums;

        int idx,orgRow, orgCol;
        vector<vector<int>> ans(r,vector<int>(c));
        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++j) {
                idx = c*i+j;
                // original
                if( idx == 0 ) {
                    orgRow = 0;
                    orgCol = 0;
                } else {
                    orgRow = idx/n;
                    orgCol = idx%n;
                }
                // cout << orgRow << " " << orgCol << endl;
                ans[i][j] = nums[orgRow][orgCol];
            }
        }
        return ans;
    }
};
