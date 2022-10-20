
// 2318. Number of Distinct Roll Sequences
// https://leetcode.com/problems/number-of-distinct-roll-sequences/




/*
 * P(n,r) -> P(6,2) = 30 permutations aka in our case 30 pairs
 * 1 2, 2 1 GCD 1
 * 1 3, 3 1 GCD 1
 * 1 4, 4 1 GCD 1
 * 1 5, 5 1 GCD 1
 * 1 6, 6 1 GCD 1
 * 2 3, 3 2 GCD 1
 * 2 4, 4 2 GCD 2
 * 2 5, 5 2 GCD 1
 * 2 6, 6 2 GCD 2
 * 3 4, 4 3 GCD 1
 * 3 5, 5 3 GCD 1
 * 3 6, 6 3 GCD 3
 * 4 5, 5 4 GCD 1
 * 4 6, 6 4 GCD 2
 * 5 6, 6 5 GCD 1
 * example for condition 1:
 * so if our current roll is 3, we could go to 1, 2[, 3], 4 and 5 next, but not to 6
 */
class Solution {
private:
    long mod = 1000000007;
    int g[7][7]; // pre,val
    long mem[10001][7][7];

    long rec(int n, int k, int prepre, int pre) {
        // n is total number of rolls we have
        // k is our current roll
        // pre is the previously rolled value
        // prepre is the rolled value before the previous one

        if( k > n )
            return 1;

        if( mem[k][prepre][pre] != -1 )
            return mem[k][prepre][pre];

        // let val be the value of our current roll
        // we can roll any value as long as we pass two conditions:
        // condition 1: gcd(pre,val) == 1
        // condition 2: val != pre and val != prepre

        long ret = 0;

        for(int val = 1; val <= 6; ++val) {
            if( val == prepre || val == pre ) // could also just do if( val == prepre )
                continue;
            if( !g[pre][val] )
                continue;
            ret += rec(n,k+1,pre,val);
        }

        return mem[k][prepre][pre] = ret % mod;
    }



public:
    int distinctSequences(int n) {
        // init possible adjacency
        memset(g,0,sizeof g);
        g[0][1] = g[0][2] = g[0][3] = g[0][4] = g[0][5] = g[0][6] = 1; // start
        g[1][2] = g[1][3] = g[1][4] = g[1][5] = g[1][6] = 1;
        g[2][1] = g[2][3] = g[2][5] = 1;
        g[3][1] = g[3][2] = g[3][4] = g[3][5] = 1;
        g[4][1] = g[4][3] = g[4][5] = 1;
        g[5][1] = g[5][2] = g[5][3] = g[5][4] = g[5][6] = 1;
        g[6][1] = g[6][5] = 1;

        // init mem
        memset(mem,-1,sizeof mem);

        return rec(n,1,0,0);
    }
};
