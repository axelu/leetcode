
// 3405. Count the Number of Arrays with K Matching Adjacent Elements
// https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/





// initialize once, precompute factorial and modinverse
long long factorial[100001];
long long inverse[100001];
bool init = false;


class Solution {
private:
    const long mod = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,mod-2);
    }

    long long modCombinations(long long n, long long k) {
        return ((factorial[n] * inverse[k]) % mod * inverse[n-k]) % mod;
    }

public:
    int countGoodArrays(int n, int m, int k) {
        if( !init ) {
            init = true;

            factorial[0] = 1LL;
            inverse[0] = 1LL;
            for(int i = 1; i <= 100000; ++i) {
                factorial[i] = (factorial[i-1] * i) % mod;
                inverse[i]   = modInverse(factorial[i]);
            }
        }


        /* pos 0: we have m choices
         * for k indices for positions in range 1..n-1 we chose to make
         *    them equal to the prior position, so we have 1 choice
         *    we have n-1 over k ways to pick the positions (combinations)
         * for the remaining positions ( n-1-k ) we have m-1 choices
         *    so (m-1) exp (n-1-k)
         *
         * formula based on the above:
         *     m * C(n-1,k) * 1 * ((m-1) exp (n-1-k))
         *     -   ------------   -------------------
         */

        int ans = (m * modCombinations(n-1, k)) % mod;
        ans = (ans * modPow(m-1, n-1-k)) % mod;

        return ans;
    }
};
