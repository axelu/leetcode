
// 3337. Total Characters in String After Transformations II
// https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/





// idea from this post
// https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/discuss/5974946/Fast-pow-or-Approach-and-clear-code
// implementation for matrix multiplication and matrix exponentiation see my solution for
// // https://leetcode.com/problems/string-transformation/


class Solution {
private:
    const long mod = 1000000007;

    vector<vector<long>> matrix_multiplication(vector<vector<long>>& a, const vector<vector<long>>& b) {
        // performs matrix multiplication aka dot product
        // https://www.mathsisfun.com/algebra/matrix-multiplying.html
        int ma = a.size();       // nbr of rows in matrix a
        int na = a[0].size();    // nbr of cols in matrix a (must match rows in matrix b)
        int nb = b[0].size();    // nbr of cols in matrix b

        // result matrix ma x nb
        vector<vector<long>> ret(ma,vector<long>(nb,0L));

        // iterate rows of matrix a
        for(int i = 0; i < ma; ++i) {
            // iterate cols of matrix b
            for(int j = 0; j < na; ++j) {
                // iterate cols of matrix b and rows of matrix a
                for(int k = 0; k < nb; ++k) {
                    long t = (a[i][j] * b[j][k]) % mod;
                    ret[i][k] = (ret[i][k] + t) % mod;
                }
            }
        }

        return ret;
    }

    vector<vector<long>> matrix_exponentiation(const vector<vector<long>>& a, long long k) {
        // performs matrix exponentiation
        // https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/
        int n = a.size(); // size of the input matrix n x n (square matrix)

        // init the result matrix as an identity matrix of size n x n
        vector<vector<long>> ret(n, vector<long>(n));
        for(int i = 0; i < n; ++i)
            ret[i][i] = 1L; // set diagonal elements to 1

        auto x = a; // copy of the input matrix

        // matrix exponentiation using binary exponentiation
        for(; k; k >>= 1) {                         // right-shift k to check its binary representation
            if( k & 1 ) {                           // if the least significant bit of k is set (odd power)
                ret = matrix_multiplication(ret,x); // multiply the result matrix r by x
            }
            x = matrix_multiplication(x, x);        // square the matrix x for the next iteration
        }

        return ret;
    }

public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        int n = s.size();

        // the count of each char in our string s becomes our matrix A
        vector<long> cnt(26,0);
        for(char c: s)
            ++cnt[c-'a'];

        vector<vector<long>> A;
        A.push_back(cnt);

        // the indicator of the transition of a char in nums becomes our matrix B
        // the matrix B is a square matrix 26x26
        // example:
        // let nums[0]  = 3, which means a becomes bcd
        //                  a b c d e f g h i j k l m n o p q r s t u v w x y z
        //    row[0] in B  {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        // let nums[24] = 5, which means y becomes zabcd (it wraps around)
        //                  a b c d e f g h i j k l m n o p q r s t u v w x y z
        //    row[24] in B {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
        //
        // nums.size() = 26
        // 1 <= nums[i] <= 25

        vector<vector<long>> B(26,vector<long>(26,0));
        for(int i = 0; i < 26; ++i) {

            // in B[i] we need to set B[i][i+1]...B[i][i+nums[i]] to 1
            // but anywhere between i+1...i+nums[i] we may get greater 25 aka wrap around
            for(int j = 0; j < nums[i]; ++j)
                B[i][(i+1+j) % 26] = 1L;
        }

        // C = A x B^t (dot product)
        // note that A and B are matricies
        // answer is sum of elements in C (matrix with 1 row)

        vector<vector<long>> Bt = matrix_exponentiation(B,t);
        vector<vector<long>> C  = matrix_multiplication(A,Bt);

        long ans = 0L;
        for(int i = 0; i < 26; ++i)
            ans = (ans + C[0][i]) % mod;

        return ans;
    }
};
