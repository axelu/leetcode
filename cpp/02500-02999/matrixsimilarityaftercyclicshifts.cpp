




// 2946. Matrix Similarity After Cyclic Shifts
// https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/





class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size();     // rows, 0-indexed
        int n = mat[0].size();  // cols, 0-indeded

        // cyclically left shift even indexed rows
        // cyclically right shift odd indexed rows

        // we could process each row individually using two pointers
        // 3 cases:
        //     k == n or (k > n and k is a multiple of n),
        //     k < n,
        //     k > n and k not a multiple of n

        if( k % n == 0 )
            return true;

        k = k % n;

        // even rows
        for(int i = 0; i < m; i += 2) {
           for(int j = n-1; j >= 0; --j) {
               int j_shifted = j - k;
               if( j_shifted < 0 )
                   j_shifted += n;
               if( mat[i][j] != mat[i][j_shifted] )
                   return false;
           }
        }

        // odd rows
        for(int i = 1; i < m; i += 2) {
           for(int j = 0; j < n; ++j) {
               int j_shifted = j + k;
               if( j_shifted >= n )
                   j_shifted -= n;
               if( mat[i][j] != mat[i][j_shifted] )
                   return false;
           }
        }

        return true;
    }
};
