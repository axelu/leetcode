
// 3700. Number of ZigZag Arrays II
// https://leetcode.com/problems/number-of-zigzag-arrays-ii/


/* see 3699. Number of ZigZag Arrays I https://leetcode.com/problems/number-of-zigzag-arrays-i/
 *     but the brute force approach I used there will not work here as constraint is too large
 * had a hunch that solution involves matrix multiplication, but could not come up with it.
 * explanations in these solutions
 * https://leetcode.com/problems/number-of-zigzag-arrays-ii/solutions/7230151/c-intuition-with-diagram-simple-implementation
 * https://leetcode.com/problems/number-of-zigzag-arrays-ii/solutions/7230647/efficient-matrix-exponentiation-solution-for-number-of-zigzag-arrays
 * https://leetcode.com/problems/number-of-zigzag-arrays-ii/solutions/7240673/cpp
 * https://leetcode.com/problems/number-of-zigzag-arrays-ii/solutions/7231585/c-matrix-dp-detailed-explanation
 */
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
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;         // number of values 0, 1, ... m-1
        int sz = 2 * m;          // either we have a[0] < a[1] > a[2] ... or a[0] > a[1] < a[2] ...

        // build transition matrix M
        vector<vector<long>> M(sz, vector<long>(sz,0));
        for(int i = 0; i < m; ++i) {
            // down, up, down -> j has to be smaller than i
            for(int j = 0; j < i; ++j)
                M[i][j + m] = 1;

            // up, down, up -> j has to be greater than i
            for(int j = i + 1; j < m; ++j)
                M[i + m][j] = 1;
        }

        // exponentiate M^(n - 1)
        vector<vector<long>> Mn = matrix_exponentiation(M, n - 1);

        // initial we can have any value, hence all ones
        vector<vector<long>> v0(sz, vector<long>(1,1L));

        // multiply Mn * v0
        // result has 1 column
        vector<vector<long>> res = matrix_multiplication(Mn, v0);

        // sum of all entries is our ans
        long ans = 0l;
        for(int i = 0; i < sz; ++i)
            ans = (ans + res[i][0]) % mod;

        return ans;
    }
};
