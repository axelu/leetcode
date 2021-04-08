
// 714. Best Time to Buy and Sell Stock with Transaction Fee
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
// day 16 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/590/week-3-march-15th-march-21st/3674/



class Solution {
private:
    int N;
    
    int dp(vector<int>& prices, int fee, int pos, int own, int notowned[], unordered_map<int,int> owned[]) {
        if( pos >= N ) return 0;
        // own: -1 indicates that we don't own currently, 
        //      otherwise it is the price that we bought the stock at
        
        // if we don't own, we have the following choices:
        //     - buy at current price
        //     - wait aka don't buy
        if( own == -1 ) {
            if( notowned[pos] != -1 ) return notowned[pos];

            // buy
            int buy = dp(prices,fee,pos+1,prices[pos],notowned,owned);
            // don't buy
            int dontbuy = dp(prices,fee,pos+1,-1,notowned,owned);
            
            return notowned[pos] = max(buy,dontbuy);
        }
        
        // if we own, we have the following choices:
        //     - sell at current price
        //           as we want to make a profit, we will sell only if prices[i]-own-fee > 0
        //     - hold aka don't sell
        
        unordered_map<int,int>::iterator f = owned[pos].find(own);
        if( f != owned[pos].end() ) return f->second;
        
        int sell = INT_MIN;
        int profit = prices[pos] - own - fee;
        if( profit  > 0 )
            sell = profit + dp(prices,fee,pos+1,-1,notowned,owned);
        int hold = dp(prices,fee,pos+1,own,notowned,owned);
        
        int res = max(sell,hold);
        
        owned[pos].insert({own,res});
        
        return res;
    }
    
    
    int _maxProfit(vector<int>& prices, int fee, int pos, bool own, int notowned[], int owned[]) {
        if( pos >= N ) return 0;
        // own: false indicates that we don't own the stock currently, 
        //      true indicates that we own the stock currently

        // not owned
        if( !own ) {
            if( notowned[pos] != -1 ) return notowned[pos];
            int buy = _maxProfit(prices,fee,pos+1,true,notowned,owned) - prices[pos];
            int dontbuy = _maxProfit(prices,fee,pos+1,false,notowned,owned);
            return notowned[pos] = max(buy,dontbuy);           
        }
        
        // owned
        if( owned[pos] != -1 ) return owned[pos];
        int sell = prices[pos] - fee + _maxProfit(prices,fee,pos+1,false,notowned,owned);
        int hold = _maxProfit(prices,fee,pos+1,true,notowned,owned);
        return owned[pos] = max(sell,hold); 
    }
    
public:
    int maxProfit(vector<int>& prices, int fee) {
        N = prices.size();
        
        // TLE case 35/44
        // int notowned[N]; for(int i = 0; i < N; ++i) notowned[i] = -1;
        // unordered_map<int,int> owned[N];
        // return dp(prices,fee,0,-1,notowned,owned);
        
        
        // solution approach #1
        // init hold to INT_MIN in order to buy stock at day 0
        // apply transaction fee when we sell the stock
        // int hold = INT_MIN;
        // int notHold = 0;
        // for(int i = 0; i < N; ++i) {
        //    // buy a share today or keep previous share
        //    hold = max(hold, notHold - prices[i]);
        //    // sell the share today or keep previous cash
        //    notHold = max(notHold, hold + prices[i] - fee);
        // }        
        // return notHold;
        
        
        int notowned[N];
        int owned[N];
        for(int i = 0; i < N; ++i) {
            notowned[i] = -1;
            owned[i] = -1;
        }
        return _maxProfit(prices,fee,0,false,notowned,owned);
    }
};
