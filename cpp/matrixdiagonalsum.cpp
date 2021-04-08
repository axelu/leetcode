
// Matrix Diagonal Sum
// https://leetcode.com/problems/matrix-diagonal-sum/


class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        auto n = mat.size();

        if( n == 1 ) return mat[0][0];

        int sum = 0;

        // primary diagonal
        for(int i = 0; i < n; ++i)
            sum += mat[i][i];

        // secondary diagonal
        int k = 0;
        for( int i = n - 1; i >= 0; --i) {
            sum += mat[k][i];
            ++k;
        }
        if( n % 2 != 0 ) {
            int h = n / 2;
            sum -= mat[h][h];
        }

        return sum;
    }
};
