
// 322. Coin Change
// https://leetcode.com/problems/coin-change/
// day 11 March 2021 challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/589/week-2-march-8th-march-14th/3668/




class Solution {
private:
    int n;
    int mem[12][10001];

    int rec(vector<int>& coins, int pos, int amount) {
        // cout << "rec pos " << pos << " amount " << amount << endl;
        if( pos >= n ) return -1;
        if( mem[pos][amount] != 0 ) return mem[pos][amount];
        if( amount % coins[pos] == 0 ) return amount/coins[pos];

        int f = amount/coins[pos];

        int ans = 10001;
        int rem,res;
        for(int i = f; i >= 0; --i) {
            rem = amount - i * coins[pos];
            res = rec(coins,pos+1,rem);
            if( res != -1 )
                ans = min(ans,res + i);
        }
        return mem[pos][amount] = ans == 10001 ? -1 : ans;
    }

public:
    int coinChange(vector<int>& coins, int amount) {
        if( amount == 0 ) return 0;
        sort(coins.begin(),coins.end(),greater<int>());
        if( amount < coins.back() ) return -1;

        // assume coins are distinct
        // greedy approach

        memset(mem,0,sizeof mem);
        n = coins.size();
        return rec(coins,0,amount);
    }
};
