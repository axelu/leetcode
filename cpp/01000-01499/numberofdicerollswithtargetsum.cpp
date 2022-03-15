
// 1155. Number of Dice Rolls With Target Sum
// https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/


class Solution {
private:
    long mod = 1000000007;

    long rec(int n, int k, int rem, int **mem) {
        if( rem < 0 || n < 0 )
            return 0L;

        if( n == 0 && rem == 0 )
            return 1L;

        if( mem[n][rem] != -1 )
            return mem[n][rem];

        // we can throw any face from 1 to k
        long ret = 0;
        for(int i = 1; i <= k; ++i) {
            ret = (ret + rec(n-1,k,rem-i,mem)) % mod;
        }

        return mem[n][rem] = ret;
    }

public:
    int numRollsToTarget(int n, int k, int target) {
        // quick check
        if( target > n*k )
            return 0;
        if( target == n*k )
            return 1;

        int **mem;
        mem = new int *[n+1];
        for(int i = 0; i <= n; i++) {
            mem[i] = new int[target+1];
            for(int j = 0; j <= target; ++j)
                mem[i][j] = -1;
        }

        return rec(n,k,target,mem);
    }
};
