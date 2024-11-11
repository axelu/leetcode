
// 3247. Number of Subsequences with Odd Sum
// https://leetcode.com/problems/number-of-subsequences-with-odd-sum/




/* intuition:
 * problem boils down to number of even and odd elements
 * to make an odd sum, we need an odd number of odd elements, so 1, 3, 5, ... elements and we can
 *   combine those with zero or more even elements.
 * example: let O represent odd element and E represent even element
 *     O E E O E E O E E
 *     we have 6 evens, so we get 2^6 = 64
 *     we can select 1 O, there are 3 of those, so 3 * 64
 *     we can select 3 Os, that gives us another   1 * 64
 *     so 4 * 64 = 256
 */
class Solution {
private:
    //   calculate number of combinations MOD 10^9+7
    //   https://barkingbogart.wordpress.com/2013/02/21/cnk-mod-1000000007/

    long mod = 1000000007;

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

    long * factorial;
    long * inverse;

    long long modCombinations(long long n, long long k) {
        return ((factorial[n] * inverse[k]) % mod * inverse[n-k]) % mod;
    }

public:
    int subsequenceCount(vector<int>& nums) {
        int odds  = 0;
        int evens = 0;
        for(int x: nums)
            if( x % 2 )
                ++odds;
            else
                ++evens;

        long long f = modPow(2, evens);


        // precompute
        int n = odds;
        long _factorial[n+1]; factorial = _factorial;
        factorial[0] = 1L;
        long _inverse[n+1]; inverse = _inverse;
        inverse[0] = 1L;
        for(long i = 1; i <= n; ++i) {
            factorial[i] = (factorial[i-1] * i) % mod;
            inverse[i]   = modInverse(factorial[i]);
        }

        long ans = 0L;

        for(int i = 1; i <= odds; i += 2) {

            ans = (ans + (modCombinations(odds, i) * f) % mod) % mod;
        }

        return ans;
    }
};
