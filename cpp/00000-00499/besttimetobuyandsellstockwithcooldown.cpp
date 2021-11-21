
// 309. Best Time to Buy and Sell Stock with Cooldown
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/



class Solution {
private:
    int n;

    int rec(vector<int>& prices, int n, int i, int own, int mem[][1002]) {
        if( i >= n )
            return 0;
        if( i == n-1 ) {
            // last trading day
            if( own < 1001 )
                return max(0,prices[i] - own);
            return 0;
        }

        if( mem[i][own] != -1 )
            return mem[i][own];

        // we have a choice(s)
        // if we own the stock:
        //     we could sell it OR
        //     we could keep it
        // if we don't own the stock:
        //     we could buy it OR
        //     we could not buy it

        int t1 = 0, t2 = 0;

        if( own < 1001 ) {
            // we own the stock at price own
            // sell (at profit)
            if( prices[i] > own )
                t1 = prices[i] - own + rec(prices,n,i+2,1001,mem);
            // keep
            t2 = rec(prices,n,i+1,own,mem);
        } else {
            // we don't own the stock
            // buy
            t1 = rec(prices,n,i+1,prices[i],mem);
            // skip
            t2 = rec(prices,n,i+1,1001,mem);
        }


        return mem[i][own] = max(t1,t2);
    }

public:
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return max(0,prices[1]-prices[0]);


        int mem[n][1002];memset(mem,-1,sizeof mem);

        return rec(prices,n,0,1001,mem);
    }
};
