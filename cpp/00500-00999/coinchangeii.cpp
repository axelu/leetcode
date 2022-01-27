
// 518. Coin Change 2
// https://leetcode.com/problems/coin-change-2/



class Solution {
private:
    int mem[301][5001];

    int rec(vector<int>& coins, int pos, int amount) {
        // amount is the remaining amount
        if( amount == 0 )
            return 1;
        if( pos == coins.size() || amount < coins[pos] )
            return 0;

        if( mem[pos][amount] != -1 )
            return mem[pos][amount];

        int ret = 0;

        // we have a choice to use the current coin
        // 0 times or
        // 1x to n times as long as n*coins[pos] <= amount
        int rem = amount, i = 0, t;
        while( rem >= 0 ) {
            int t = rec(coins,pos+1,rem);
            if( t )
                ret += t;
            ++i;
            rem = amount - coins[pos]*i;
        }
        return mem[pos][amount] = ret;
    }

public:
    int change(int amount, vector<int>& coins) {
        sort(coins.begin(),coins.end());
        memset(mem,-1,sizeof mem);
        return rec(coins,0,amount);
    }
};
