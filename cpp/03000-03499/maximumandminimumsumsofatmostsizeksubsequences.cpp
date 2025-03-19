
// 3428. Maximum and Minimum Sums of at Most Size K Subsequences
// https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/






// initialize once, precompute factorial and modinverse
long long factorial[100001];
long long inverse[100001];
long long _modCombinations[100001][71];
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
    int minMaxSums(vector<int>& nums, int k) {
        if( !init ) {
            init = true;

            factorial[0] = 1LL;
            inverse[0] = 1LL;
            for(int i = 1; i <= 100000; ++i) {
                factorial[i] = (factorial[i-1] * i) % mod;
                inverse[i]   = modInverse(factorial[i]);
            }

            // precompute modCombinations to speed this up
            for(int i = 1; i <= 100000; ++i)
                for(int j = 1; j <= min(i,70); ++j)
                    _modCombinations[i][j] = modCombinations(i, j);
        }

        int n = nums.size(); // 1 <= nums.length <= 1e5
        // 0 <= nums[i] <= 1e9
        // 1 <= k <= min(100, nums.length)

        // order of elements does not matter
        sort(begin(nums), end(nums));

        long ans = 0;

        for(int i = 0; i < n; ++i) {
            int d = n - i;

            // the current element is the minimum for any subsequence
            // starting at i
            // subsequence with length of 1
            ans = (ans + (long)nums[i]) % mod;
            // there are (n-1) - i positions remaining to our left
            // subsequence with length 2...min(k, n-i)
            // we need to distribute (l-1) picks
            if( i < n-1 ) {
                for(int l = 2; l <= min(k, n-i); ++l)
                    // ans = ans + (nums[i] * modCombinations((n-1) - i, l-1));
                    ans = (ans + (((long)nums[i] * _modCombinations[(n-1) - i][l-1]) % mod)) % mod;
            }

            // the current element is the maximum for any subarray
            // ending at i
            // subsequence with length of 1
            ans = (ans + (long)nums[i]) % mod;
            // there are i positions to our right
            // subsequence with length 2...min(k, i)
            // we need to distribute (l-1) picks
            if( i > 0 )
                for(int l = 2; l <= min(k, i+1); ++l)
                    // ans = ans + (nums[i] * modCombinations(i, l-1));
                    ans = (ans + (((long)nums[i] * _modCombinations[i][l-1]) % mod)) % mod;
        }

        return ans;
    }
};
