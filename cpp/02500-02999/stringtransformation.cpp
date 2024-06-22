
// 2851. String Transformation
// https://leetcode.com/problems/string-transformation/






/* example 1 s = "abcd", t = "cdab", k = 2
 *  let n be the length of s and t, s.length == t.length
 *   in order for there to be any solution, t has to be a rotation of s
 *   so one step will be to find the rotations (plural!) of s that result in t
 *   in our example, s has been rotated two times to become t, so we have one rotation of 2.
 *   now the question becomes: how can we get to a rotation of 2 in k operations, in our example in k = 2 operations?
 *   there are 2 ways:
 *     rotate by 1 two times OR
 *     rotate by 3 two times
 *  rotate by 1 two times: abcd -> dabc -> cdab
 *  rotate by 3 two times: abcd -> bcda -> cdab
 *    rotation by 3 two times works, because (3 + 3) % n = (3 + 3) % 4 = 6 % 4 = 2, where 2 is number of times s was rotated
 *  rotating by 0 or n leads to the same string, so lets ignore 0 and n rotations
 *  so in our example we can rotate the string 1,2,3 times
 *  we are looking for the permutations of length k of those integers 1, 2 and 3 (basically of [1,n-1], that have our 1st character
 *  end up in the positions that s got rotated to, or said differently, where their sum % n = rotation
 *  so in our example:
 *                                                                abcd
 *                      -----------                            -----------                            -----------
 * k = 1                rotate by 1                            rotate by 2                            rotate by 3
 *                         dabc                                   cdab                                   bcda
 * position of 1st char     1                                       2                                       3
 * k = 2   -------------------------------------  -------------------------------------  -------------------------------------
 *         rotate by 1  rotate by 2  rotate by 3  rotate by 1  rotate by 2  rotate by 3  rotate by 1  rotate by 2  rotate by 3
 *            cdab         bcda         abcd         bcda         abcd         dabc         abcd         dabc         cdab
 *              2             3         0               3         0             1           0             1             2
 *              -                                                                                                       -
 * we see that our first char ends up in position 2 two times.
 * so as we can see, rotating 1,1 and rotating 3,3 gets 'a' into position 2 after those rotations, so we have 2 ways with 2 operations
 * if we would go on to k = 3 operations:
 * k = 3  continuing vertically for space reasons
 *            cdab         bcda         abcd         bcda         abcd         dabc         abcd         dabc         cdab
 *        r 1 bcda 3   r 1 abcd 0   r 1 dabc 1   r 1 abcd 0   r 1 dabc 1   r 1 cdab 2   r 1 dabc 1   r 1 cdab 2   r 1 bcda 3
 *        r 2 abcd 0   r 2 dabc 1   r 2 cdab 2   r 2 dabc 1   r 2 cdab 2   r 2 bcda 3   r 2 cdab 2   r 2 bcda 3   r 2 abcd 0
 *        r 3 dabc 1   r 3 cdab 2   r 3 bcda 3   r 3 cdab 2   r 3 bcda 3   r 3 abcd 0   r 3 bcda 3   r 3 abcd 0   r 3 dabc 1
 * lets take above and create a matrix that counts how many times the 1st char shows up at a given position after k operations
 *       position of 1st char  0  1  2  3
 * number of operations k  1   0  1  1  1
 *                         2   3  2  2  2
 *                         3   6  7  7  7
 *                         4  21 20 20 20
 *                         ...
 * we see that after x operations the 1st char ends up in position 0 a number of times, and the 1st char ends up
 * the same number of times in any non-zero position, so we can collapse our matrix to only 2 positions
 * we have a recursive relationship
 * so our second step needs to be to find how many ways k integers in the range [1,n-1] add up to a given rotation % n.
 * let dp[k][i] be the number of ways to get the 1st char to position i after k operations
 * because we only need to distinguish position 0 from any non-zero positions, i is either 0 or 1 (1 representing all non-zero positions)
 * state transitions
 * dp[0][0] = 1
 * dp[0][1] = 0
 * dp[k][0] = dp[k - 1][1] * (n - 1)
 * dp[k][1] = dp[k - 1][0] + dp[k - 1][1] * (n - 2)
 *
 * k is very large, so how to calculate dp[k][i] very fast?
 * see here: https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/
 * we can use matrix multiplication
 *
 * transition
 * dp[k][0] =                0 + dp[k - 1][1] * (n - 1)
 *                           -                  -------
 * dp[k][1] = dp[k - 1][0] * 1 + dp[k - 1][1] * (n - 2)
 *                           -                  ------
 * vector (dp[t - 1][0], dp[t - 1][1])
 * multiplies matrix
 * [0    , 1]
 * [n - 1, n - 2]
 * to vector (dp[t][0], dp[t][1]).
 * so we calculate the kth power of the matrix via matrix exponentiation
 */
class Solution {
private:
    long mod = 1000000007;

    void kmp_table(string& W, int T[]) {
        // https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

        // input:  an array of characters, W (the word to be analyzed)
        // output: an array of integers, T (the table to be filled)

        int pos = 1; // current position we are computing in t
        int cnd = 0; // zero-based index in w of the next character of the current candidate substring

        T[0] = -1;

        while(pos < W.size()) {
            if( W[pos] == W[cnd] ) {
                T[pos] = T[cnd];
            } else {
                T[pos] = cnd;
                while(cnd >= 0 && W[pos] != W[cnd]) {
                    cnd = T[cnd];
                }
            }
            ++pos;
            ++cnd;
        }

        T[pos] = cnd; // only needed when all word occurrences are searched
    }

    int kmp_search(string& S, string& W, int P[]) {
        // https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

        // input:   an array of characters, S (the text to be searched)
        //          an array of characters, W (the word sought)
        // output:  an array of integers, P (positions in S at which W is found)
        //          an integer, nP (number of positions)

        int j = 0; // the position of the current character in S
        int k = 0; // the position of the current character in W
        int T[W.size()+1]; kmp_table(W,T); // Partial Match

        int nP = 0;

        while(j < S.size()) {
            if( W[k] == S[j] ) {
                ++j;
                ++k;
                if( k == W.size() ) {
                    // occurrence found, if only first occurrence is needed, m ← j - k  may be returned here
                    P[nP] = j - k; nP = nP + 1;
                    k = T[k]; // T[length(W)] can't be -1
                }
            } else {
                k = T[k];
                if( k < 0 ) {
                    ++j;
                    ++k;
                }
            }
        }
        return nP;
    }

    vector<long> f(int n, int k) {

        long dp0 = 1; // dp[0][0] = 1
        long dp1 = 0; // dp[0][1] = 0
        for(int i = 1; i <= k; ++i) {

            long dp0_nxt = (dp1 * (n-1)) % mod;
            long dp1_nxt = (dp0 + (dp1 * (n-2)) % mod) % mod;

            dp0 = dp0_nxt;
            dp1 = dp1_nxt;
        }

        return {dp0, dp1};
    }

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
    int numberOfWays(string s, string t, long long k) {
        int n = s.size(); // s.size() == t.size()

        // step 1: find the rotations (plural!) of s that result in t
        // Knuth Morris Pratt KMP
        string t2 = t + t;
        int P[2 * n]; memset(P,0,sizeof P);
        int nP = kmp_search(t2,s,P);
        if( nP == 0 )
            return 0; // t is not a rotation of s

        // step 2: find how many ways k integers in the range [1,n-1] add up to a given rotation % n
        // brute force
        // auto dpk = f(n,k);
        // matrix exponentiation
        vector<vector<long>> matrix = {{0,     1    },
                                       {n - 1, n - 2}};
        auto dpk = matrix_exponentiation(matrix, k)[0];


        long ans = 0L;

        if( P[0] == 0 )
            ans = dpk[0];
        // we concatenated t with itself, so only look up to n-1 for starts
        if( P[nP-1] == n )
            --nP;
        long nbr_non_zero_rotations = P[0] == 0 ? nP - 1 : nP;

        ans = (ans + (nbr_non_zero_rotations * dpk[1]) % mod) % mod;

        return ans;
    }
};
