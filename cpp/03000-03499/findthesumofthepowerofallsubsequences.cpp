
// 3082. Find the Sum of the Power of All Subsequences
// https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/




class Solution {
private:
    const long mod = 1000000007;

    int modular_pow(unsigned long long base, int exponent) {
        unsigned long long c = 1;
        for(int i = 0; i < exponent; ++i)
            c = (c * base) % mod;
        return c;
    }

    long mem[100][101][101];

    long rec(vector<int>& nums, int n, int pos, int sum, int taken, int k) {
        if( sum > k )
            return 0;

        if( sum == k ) {
            // key insight from hint
            // we found a subsequence of length taken, it contributes
            // 2 ^ (n - taken) to the solution
            return modular_pow(2, n - taken);
        }

        if( pos == n )
            return 0;

        if( mem[pos][sum][taken] != -1L )
            return mem[pos][sum][taken];

        long ret = 0LL;

        // we have a choice
        //     don't pick the current pos OR
        //     pick the current pos

        ret = (ret + rec(nums, n, pos+1, sum, taken, k)) % mod;
        ret = (ret + rec(nums, n, pos+1, sum+nums[pos], taken + 1, k)) % mod;

        return mem[pos][sum][taken] = ret;
    }

public:
    int sumOfPower(vector<int>& nums, int k) {
        int n = nums.size();

        memset(mem,-1,sizeof mem);
        return rec(nums, n, 0, 0, 0, k);
    }
};
