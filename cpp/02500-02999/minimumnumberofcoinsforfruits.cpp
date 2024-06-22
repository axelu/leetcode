
// 2944. Minimum Number of Coins for Fruits
// https://leetcode.com/problems/minimum-number-of-coins-for-fruits/




class Solution {
private:

    int mem[1001][1002];

    int rec(vector<int>& prices, int n, int i, int k) {
        // prices is 1-indexed !!!
        if( i == n+1 )
            return 0;

        if( mem[i][k] != -1 )
            return mem[i][k];

        // k is the index till which the fruit is free, said differently
        // if i < k we can skip buying, but if i == k we have to buy the current fruit

        // we have a choice
        //    don't buy the current fruit (if it is still free) OR
        //    buy the current fruit

        int a = INT_MAX;
        if( i < k )
            a = rec(prices,n,i+1,k);

        int b = prices[i-1] + rec(prices,n,i+1,min(n+1,i+i+1));

        return mem[i][k] = min(a,b);
    }

public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        memset(mem,-1,sizeof mem);
        return rec(prices,n,1,1);
    }
};
