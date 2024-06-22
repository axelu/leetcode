
// 2969. Minimum Number of Coins for Fruits II
// https://leetcode.com/problems/minimum-number-of-coins-for-fruits-ii/




// see for good apprach
// https://leetcode.com/problems/minimum-number-of-coins-for-fruits-ii/discuss/4432069/Linear-time-DP-in-C%2B%2B-Java-and-Python



class Solution {
private:
    int n;
    vector<long> bit; // binary indexed tree fenwick tree 0 indexed

    long getmin(int r) {
        long ret = INT_MAX;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void update(int idx, long val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], val);
    }

    long rec(vector<int>& prices, int pos) {
        if( pos >= n )
            return 0L;

        if( bit[pos] != INT_MAX )
            return bit[pos];

        // we have to acquire all fruit
        //     lets acquire the fruit at pos,
        //     which means 'at minimum' we would need to continue at
        //     pos + pos + 2

        long ret = prices[pos] + rec(prices, pos + pos + 2);

        // however, that may not be optimal
        rec(prices, pos + 1);

        // now lets determine if buying the current fruit and the
        // fruit where we must continue is better than bying the
        // current fruit and a fruit in the free range

        long mn = getmin(min(n-1, pos + pos + 1));

        ret = min(ret, prices[pos] + mn);

        update(pos,ret);

        return ret;
    }

public:
    int minimumCoins(vector<int>& prices) {
        n = prices.size();

        bit.assign(n,INT_MAX);
        return rec(prices,0);
    }
};
