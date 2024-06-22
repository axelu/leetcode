
// 2338. Count the Number of Ideal Arrays
// https://leetcode.com/problems/count-the-number-of-ideal-arrays/







/* the brute force solution below eventually runs into TLE
 * so we need to look for a different approach
 * example n = 5, maxValue = 10
 * so where all 5 positions are equal gives us one set of ideal arrays each
 * let us now see when we have 2 uniqe numbers to distribute into the 5 positions
 * let us start with where position 0 is 1
 * 1 2 2 2 2
 * 1 1 2 2 2
 * 1 1 1 2 2
 * 1 1 1 1 2
 * the problem is now: how many ways can we distribute 5 identical objects into 2 non-empty bins?
 * https://brilliant.org/wiki/identical-objects-into-distinct-bins/
 * stars and bars problem: stars = n, bars = unique ints - 1
 * 1 | 2   2   2   2
 * 1   1 | 2   2   2
 * 1   1   1 | 2   2
 * 1   1   1   1 | 2
 * nCr(n-1,r-1) -> nCr(4,1) = 4
 * lets assume we have 3 unique numbers
 * 1 | 2 | 4   4   4
 * 1 | 2   2 | 4   4
 * 1 | 2   2   2 | 4
 * 1   1 | 2 | 4   4
 * 1   1 | 2   2 | 4
 * 1   1   1 | 2 | 4
 * nCr(n-1,r-1) -> nCr(4,2) = 6
 * so for a given length and a given number of unique integers, we can calculate how many ways we can build distinct ideal areas
 * by asking: how many ways can we distribute n identical objects into r non-empty bins? where r = number distinct ints - 1
 *
 * now the questions to answer are:
 * if 1 <= maxValue <= 1e4, then in our worst case scenario maxValue = 10000, how many unique numbers could we have?
 * if we assume 1 in the 1st position n >= 14, we could have max 14 unique ints in an ideal array.
 * 0 1 2 3  4 5   6   7   8   9   10   11   12   13
 * 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192
 *
 * optimization: so we could precalculate nCr(n,r) for n up to 10000 and r up to 14
 *
 * our remaining question then becomes:
 * how many times do we have 1, 2, 3, ... unique ints given n and maxValue?
 *
 */
class Solution {
private:
    const long MOD = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % MOD;
            a = (a*a) % MOD;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,MOD-2);
    }

    long long modCombinations(long long n, long long k) {
        // regular combinations formula C(n,k) = n!/(k!(n-k)!)
        // return C(n,k) mod MOD
        long long numerator = 1; // n*(n-1)* ... * (n-k+1)
        int i;
        for(i=0;i<k;i++) numerator = (numerator*(n-i))%MOD;

        long long denominator = 1; // k!
        for(i=1;i<=k;i++) denominator = (denominator*i) %MOD;

        long long res = modInverse(denominator);
        res = (res*numerator)%MOD;
        return res;
    }

public:
    int idealArrays(int n, int maxValue) {

        long ans = maxValue; // ideal array with 1 unique value

        long _nxt[maxValue+1]; long * nxt = _nxt;
        for(int i = 1; i <= maxValue; ++i)
            nxt[i] = 1L;

        long _cur[maxValue+1]; long * cur = _cur;


        for(int i = 14-2; i >= 0; --i) {
            // cout << "number unique " << 14 - i << endl;

            for(int j = 1; j <= maxValue; ++j) {
                cur[j] = 0L;
                int k = 2;
                while( j * k <= maxValue ) {
                    cur[j] = (cur[j] + nxt[j * k]) % MOD;
                    ++k;
                }
                // cout << "  start " << j << " count of uniqe combinations " << cur[j] << endl;

                ans = (ans + ((cur[j] * (modCombinations(n - 1, 14 - i - 1))) % MOD)) % MOD;
            }

            // swap
            long * t = nxt;
            nxt = cur;
            cur = t;
        }

        return ans;
    }
};

/*
// brute force
class Solution {
public:
    int idealArrays(int n, int maxValue) {

        const long mod = 1000000007;

        long _nxt[maxValue+1]; long * nxt = _nxt;
        for(int i = 1; i <= maxValue; ++i)
            nxt[i] = 1L;

        long _cur[maxValue+1]; long * cur = _cur;


        for(int i = n-2; i >= 0; --i) {

            for(int j = 1; j <= maxValue; ++j) {
                cur[j] = 0L;
                int k = 1;
                while( j * k <= maxValue ) {
                    cur[j] = (cur[j] + nxt[j * k]) % mod;
                    ++k;
                }
            }

            // swap
            long * t = nxt;
            nxt = cur;
            cur = t;
        }

        long ans = 0L;
        for(int j = 1; j <= maxValue; ++j)
            ans = (ans + nxt[j]) % mod;

        return ans;
    }
};
*/
