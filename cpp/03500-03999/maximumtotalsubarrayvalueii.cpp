
// 3691. Maximum Total Subarray Value II
// https://leetcode.com/problems/maximum-total-subarray-value-ii/


// solution based on hints given in the problem

/*
           l       r
    ======================
     1 x x |       |
     2 x   x       |
     3 x   | x     |
     4 x   |       x
     5 x   |       |  x
    ----------------------
     6     x x     |
     7     x       x
     8     x       |  x
    ----------------------
     9     | x  x  |
    10     | x     x
    11     | x     |  x
    ---------------------
    12     |       x  x
    ---------------------
    13     |       |  x x


 */
class Solution {
private:
    // segment tree that returns min and max in given interval
    pair<int,int> t[200000]; // 4 * max n; max n 50000

    pair<int, int> combine(pair<int,int> a, pair<int,int> b) {
        return make_pair(min(a.first,b.first),max(a.second,b.second));
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = make_pair(a[tl],a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    pair<int, int> get_min_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return make_pair(INT_MAX,INT_MIN);
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(get_min_max(v*2, tl, tm, l, min(r, tm)),
            get_min_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        // 1 <= n == nums.length <= 5 * 1e​4
        // 0 <= nums[i] <= 1e9
        // 1 <= k <= min(1e5, n * (n + 1) / 2)
        int n = nums.size();

        build(nums,1,0,n-1);

        long long ans = 0LL;

        // array<int,3> 0: max(nums[l..r]) - min(nums[l..r]); 1: l; 2: r
        auto cmp = [](const array<int,3>& a, const array<int,3>& b){
            return a[0] < b[0];
        };
        priority_queue<array<int,3>, vector<array<int,3>>, decltype(cmp)> pq(cmp);

        for(int l = 0; l < n-1; ++l) {
            auto min_max = get_min_max(1, 0, n-1, l, n-1);
            if( min_max.second - min_max.first == 0 )
                break;
            pq.push({min_max.second - min_max.first, l, n-1});
        }

        while( !pq.empty() && k > 0 ) {
            long long val = pq.top()[0];
            int l = pq.top()[1];
            int r = pq.top()[2];
            pq.pop();

            ans += val;

            if( l < r-1 ) {
                auto min_max = get_min_max(1, 0, n-1, l, r-1);
                pq.push({min_max.second - min_max.first, l, r-1});
            }

            --k;
        }

        return ans;
    }
};
