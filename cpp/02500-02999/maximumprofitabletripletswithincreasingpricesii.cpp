
// 2921. Maximum Profitable Triplets With Increasing Prices II
// https://leetcode.com/problems/maximum-profitable-triplets-with-increasing-prices-ii/


class Solution {
private:
    int t[10004]; // segment tree memory efficient indexing
    
    void inittree() {
        for(int i = 0; i < 10004; ++i)
            t[i] = -2000001;
    }
    
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
        //    prices per constraint are 1 - 5000
        //    initialize the tree with -2000001
        // traverse left to right recording max profit for any prices lower than current price
        //     to our left, update the tree as we move along
        // traverse right to left recording max profit for any prices lower than current price
        //     to our right, update the tree as we move along
        // traverse one more time adding current element's profit
        //     + max left profit and max right profit
        
        // left to right
        int l2r[n];
        inittree();
        update(1,0,5001,prices[0],profits[0]);
        for(int i = 1; i < n-1; ++i) {
            l2r[i] = get_max(1,0,5001,0,prices[i]-1);
            update(1,0,5001,prices[i],profits[i]);
        }
        
        // right to left
        int r2l[n];
        inittree();
        update(1,0,5001,prices[n-1],profits[n-1]);
        for(int i = n-1; i >= 1; --i) {
            r2l[i] = get_max(1,0,5001,prices[i]+1,5001);
            update(1,0,5001,prices[i],profits[i]);
        }
        
        int ans = -1;
        for(int i = 1; i < n-1; ++i)
            ans = max(ans, l2r[i] + profits[i] + r2l[i]);
         
        return ans < 0 ? -1 : ans;
    }
};



///////////////////////////////////////////////////////////////////////////////
// Note:
// my same solution for 2907. Maximum Profitable Triplets With Increasing Prices I
//   https://leetcode.com/problems/maximum-profitable-triplets-with-increasing-prices-i
// passes 2108 / 2113 test cases and then TLE
//   case 2109 runs in ~2500ms with correct result
