
// 3573. Best Time to Buy and Sell Stock V
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/


class Solution {
private:
    const long long INF = 1e9 * 1e3 + 1;

    // mem day 0-2999, state 0-2, k 1-1500
    vector<vector<vector<long long>>> mem;

    long long rec(vector<int>& prices, int n, int day, int state, int k) {

        // state 0 we don't own nor short sold, 1 we own, 2 we short sold

        if( k == 0 )
            return 0LL;

        // last day
        // owned or not, short sold or not, we are done
        if( day == n-1 ) {
            if( state == 0 )
                return 0LL;
            else if( state == 1 )
                return (long long)prices[n-1]; 
            else if( state == 2 )
                return -(long long)prices[n-1]; 
        }

        if( mem[day][state][k] != -INF )
            return mem[day][state][k];

        // we have a choice
        //     don't do anything OR
        //     buy if we currently don't own or if we short sold OR
        //     sell if we currently own or we don't own (short sell)

        // don't do anything
        long long a = rec(prices, n, day+1, state, k);

        long long b = -INF;
        long long c = -INF;

        if( state == 0 ) {
            // we don't own currently
            b = -(long long)prices[day] + rec(prices, n, day+1, 1, k); // buy
            c = (long long)prices[day] + rec(prices, n, day+1, 2, k); // short sell
        } else if( state == 1 ) {
            // we own currently
            b = (long long)prices[day] + rec(prices, n, day+1, 0, k-1); // sell
        } else { // state == 2
            // we short sold
            b = -(long long)prices[day] + rec(prices, n, day+1, 0, k-1); // buy back
        }

        return mem[day][state][k] = max({a,b,c});
    }

public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();

        mem.assign(n, vector<vector<long long>>(3,vector<long long>(k+1,-INF)));

        return rec(prices, n, 0, 0, k);
    }
};

