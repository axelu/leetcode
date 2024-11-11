
// 3336. Find the Number of Subsequences With Equal GCD
// https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/





class Solution {
private:
    const long mod = 1000000007;

    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    long mem[200][201][201];

    long rec(vector<int>& nums, int n, int i, int gcd1, int gcd2 ) {
        if( i == n ) {
            // we must have at least used one nums[i], so discard if gcd's still 0
            return gcd1 != 0 && gcd2 != 0 && gcd1 == gcd2 ? 1L : 0L;
        }

        if( mem[i][gcd1][gcd2] != -1L )
            return mem[i][gcd1][gcd2];

        // we have choices
        //     include nums[i] in seq1 OR
        //     include nums[i] in seq2 OR
        //     do not include either

        // if we are just starting out, gcd1 or gcd2 will be 0, which our gcd function handles
        int gcd1_new = gcd(nums[i], gcd1);
        int gcd2_new = gcd(nums[i], gcd2);

        long ret = 0L;
        ret = (ret + rec(nums, n, i+1, gcd1_new, gcd2)) % mod;
        ret = (ret + rec(nums, n, i+1, gcd1, gcd2_new)) % mod;
        ret = (ret + rec(nums, n, i+1, gcd1, gcd2)) % mod;

        return mem[i][gcd1][gcd2] = ret;
    }


public:
    int subsequencePairCount(vector<int>& nums) {
        // 1 <= nums.length <= 200
        // 1 <= nums[i] <= 200

        int n = nums.size();

        memset(mem,-1,sizeof mem);
        return rec(nums, n, 0, 0, 0);
    }
};
