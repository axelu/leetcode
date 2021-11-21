
// 1329. Sort the Matrix Diagonally
// https://leetcode.com/problems/sort-the-matrix-diagonally/
// day 23 January 2021 challenge
// https://leetcode.com/explore/featured/card/january-leetcoding-challenge-2021/582/week-4-january-22nd-january-28th/3614/



class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        int nbrDiagonals = m+n-1;
        vector<vector<int>> diagonals(nbrDiagonals);

        // walk the matrix row by row and fill diagonals
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                // idx of diagonal
                int idx = i - j;
                if( idx < 0 ) idx = m-1-idx;
                diagonals[idx].push_back(mat[i][j]);
            }
        }
        // sort the values in each diagonal
        for(vector<int>& diagonal : diagonals)
            sort(diagonal.begin(),diagonal.end());

        // walk the matrix row by row and update based on sorted diagonals
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                // idx of diagonal
                int idx = i - j;
                if( idx < 0 ) idx = m-1-idx;
                // idx of value in the diagonal
                // smaller of i or j
                int idxD = i < j ? i : j;
                mat[i][j] = diagonals[idx][idxD];
            }
        }

        return mat;
    }
};
