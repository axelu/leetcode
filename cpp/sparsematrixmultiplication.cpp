
// 311. Sparse Matrix Multiplication
// https://leetcode.com/problems/sparse-matrix-multiplication/



class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        // mat1: m x k
        // mat2: k x n
        int m = mat1.size();    // rows mat1
        int k = mat1[0].size(); // cols mat1 = rows mat2
        int n = mat2[0].size(); // cols mat2

        // regular matrix multiplication
        // res[i][j] += mat1[i][l] * mat2[l][j]

        // sparse matrix has "lots of zero's"

        // idea: get non-zero elements of mat1 and multiply/sum them
        vector<array<int,2>> mat1nonzero[k];
        for(int i = 0; i < m; ++i)
            for(int l = 0; l < k; ++l)
                if( mat1[i][l] != 0 )
                    mat1nonzero[l].push_back({i,mat1[i][l]});

        vector<vector<int>> ans(m,vector<int>(n,0));
        for(int l = 0; l < k; ++l)
            for(int j = 0; j < n; ++j)
                if( mat2[l][j] != 0 )
                    for(int o = 0; o < mat1nonzero[l].size(); ++o) {
                        int i = mat1nonzero[l][o][0];
                        int p = mat1nonzero[l][o][1] * mat2[l][j];
                        ans[i][j] += p;
                    }

        return ans;
    }
};
