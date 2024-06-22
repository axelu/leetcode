
// 3033. Modify the Matrix
// https://leetcode.com/problems/modify-the-matrix/




class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        int max_col[n];memset(max_col,-1,sizeof max_col);
        for(int j = 0; j < n; ++j)
            for(int i = 0; i < m; ++i)
                max_col[j] = max(max_col[j], matrix[i][j]);

        vector<vector<int>> ans(m, vector<int>(n));

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                ans[i][j] = matrix[i][j] == -1 ? max_col[j] : matrix[i][j];

        return ans;
    }
};
