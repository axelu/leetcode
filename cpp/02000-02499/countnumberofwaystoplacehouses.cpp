
// 2320. Count Number of Ways to Place Houses
// https://leetcode.com/problems/count-number-of-ways-to-place-houses/




class Solution {
    int N;

    long mod = 1000000007;
    long mem[10000];

    long rec(int i) {
        if( i >= N )
            return 1;

        if( mem[i] != -1 )
            return mem[i];

        // if we are at i, we can place a house at i
        // we have a choice
        //    don't place a house at i
        //    please a house at i

        long ret = rec(i+1);

        ret = (ret + rec(i+2)) % mod;

        return mem[i] = ret;
    }

public:
    int countHousePlacements(int n) {
        N = n;
        memset(mem,-1,sizeof mem);
        long t = rec(0);
        return (t*t) % mod;
    }
};
