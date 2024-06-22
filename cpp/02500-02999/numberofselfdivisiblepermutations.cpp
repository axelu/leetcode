
// 2992. Number of Self-Divisible Permutations
// https://leetcode.com/problems/number-of-self-divisible-permutations/





class Solution {
private:
    int mem[15][32767];

    int rec(const int n, const int i, const int mask) {
        if( i == n )
            return 1;

        if( mem[i][mask] != -1 )
            return mem[i][mask];

        // we have a choice
        //    we can put any unsed number at pos if one of the two conditions hold

        int ret = 0;

        for(int k = 0; k < n; ++k) {
            if( mask & (1<<k) )
                continue;

            if( (k+1) % (i+1) == 0 || (i+1) % (k+1) == 0 ) {
                int mask_new = mask | (1<<k);
                ret = ret + rec(n,i+1,mask_new);
            }
        }

        return mem[i][mask] = ret;
    }


public:
    int selfDivisiblePermutationCount(int n) {
        // 1 <= n <= 15
        // permutations of the 1-indexed array nums = [1,2,3,4...,n]
        // worst case n = 15 -> 1307674368000 permutations

        memset(mem,-1,sizeof mem);
        return rec(n,0,0);
    }
};
