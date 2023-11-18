
// 2907. Maximum Profitable Triplets With Increasing Prices I
// https://leetcode.com/problems/maximum-profitable-triplets-with-increasing-prices-i/





class Solution {
private:
    vector<int> t; // segment tree memory efficient indexing

    int get_max(int v, int tl, int tr, int l, int r) {
        // cout << "get_max v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return -2000001;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = max(t[v],new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }


public:
    int maxProfit(vector<int>& prices, vector<int>& profits) {
        int n = prices.size(); // prices.size() == profits.size()
                               // 1 <= prices[i] <= 10^6

        // build a segment tree
        //    get the unique prices, those are our leaves
        //    initialize the tree with -2000001
        // traverse left to right recording max profit for any prices lower than current price
        //     to our left, update the tree as we move along
        // traverse right to left recording max profit for any prices lower than current price
        //     to our right, update the tree as we move along
        // traverse one more time adding current element's profit
        //     + max left profit and max right profit

        set<int> _prices;
        for(int price: prices)
            _prices.insert(price);

        // left to right
        int l2r[n];
        t.assign(2*_prices.size(),-2000001);
        auto f = _prices.lower_bound(prices[0]);
        int pos = distance(_prices.begin(),f);
        update(1,0,_prices.size()-1,pos,profits[0]);
        for(int i = 1; i < n-1; ++i) {
            f = _prices.lower_bound(prices[i]);
            pos = distance(_prices.begin(),f);
            if( pos > 0 )
                l2r[i] = get_max(1,0,_prices.size()-1,0,pos-1);
            else
                l2r[i] = -2000001;
            update(1,0,_prices.size()-1,pos,profits[i]);
        }

        // right to left
        int r2l[n];
        t.assign(2*_prices.size(),-2000001);
        f = _prices.lower_bound(prices[n-1]);
        pos = distance(_prices.begin(),f);
        update(1,0,_prices.size()-1,pos,profits[n-1]);
        for(int i = n-1; i >= 1; --i) {
            f = _prices.lower_bound(prices[i]);
            pos = distance(_prices.begin(),f);
            if( pos < n-1 )
                r2l[i] = get_max(1,0,_prices.size()-1,pos+1,_prices.size()-1);
            else
                r2l[i] = -2000001;
            update(1,0,_prices.size()-1,pos,profits[i]);
        }

        int ans = -2000001;
        for(int i = 1; i < n-1; ++i)
            ans = max(ans, l2r[i] + profits[i] + r2l[i]);

        return ans < 0 ? -1 : ans;
    }
};
