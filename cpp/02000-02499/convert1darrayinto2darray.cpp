
// 2022. Convert 1D Array Into 2D Array
// https://leetcode.com/problems/convert-1d-array-into-2d-array/





class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        int osz = original.size();

        if( m * n != osz )
            return {};

        vector<vector<int>> ans(m,vector<int>(n));

        int i,j;
        for(int k = 0; k < osz; ++k) {
            i = k/n;
            j = k%n;
            ans[i][j] = original[k];
        }

        return ans;
    }
};
