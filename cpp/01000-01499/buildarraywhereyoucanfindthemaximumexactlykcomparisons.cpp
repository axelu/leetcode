// 1420. Build Array Where You Can Find The Maximum Exactly K Comparisons
// https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/



class Solution {
private:
    long mod = 1000000007;

    long mem[50][101][51]; // n,m,k -> i,pre,k

    long rec(int n, int m, int k, int i, int pre) {
        // k is remaining search cost
        // pre is the max seen so far
        if( i == n && k == 0 )
            return 1;
        if( i == n )
            return 0;

        if( mem[i][pre][k] != -1L )
           return mem[i][pre][k];

        long ret = 0;

        // we have a choice
        if( k == 0 ) {
            for(int j = 1; j <= pre; ++j) {
                ret += rec(n,m,k,i+1,pre);
            }

        } else {
            int k_new, pre_new;
            for(int j = 1; j <= m; ++j) {
                k_new   = j <= pre ? k : k-1;
                pre_new = max(pre,j);
                ret += rec(n,m,k_new,i+1,pre_new);
            }
        }

        // return ret;
        return mem[i][pre][k] = ret % mod;
    }

public:
    int numOfArrays(int n, int m, int k) {
        if( k == 0 || m < k ) // we cannot build any array
            return 0;

        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= m; ++j)
                for(int o = 0; o <= k; ++o)
                    mem[i][j][o] = -1L;

        return rec(n,m,k,0,0);
    }
};
