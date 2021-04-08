
// 867. Transpose Matrix
// https://leetcode.com/problems/transpose-matrix/



class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size();      // rows of original matrix
        int n = matrix[0].size();   // cols of original matrix

        vector<vector<int>> ans(n,vector<int>(m));
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                ans[j][i] = matrix[i][j];
            }
        }

        return ans;
    }
};
