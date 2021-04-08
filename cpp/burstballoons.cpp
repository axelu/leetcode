
// 312. Burst Balloons
// https://leetcode.com/problems/burst-balloons/
// day 13 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/570/week-2-december-8th-december-14th/3564/


class Solution {
private:
    map<vector<int>,int> dp;
    int _maxCoins(vector<int>& nums) {
        size_t n = nums.size();
        if( n == 1 ) return nums[0];
        auto f = dp.find(nums);
        if( f != dp.end() ) return f->second;

        int mx = -1;
        int val,a,t;
        int r = nums[0];
        nums.erase(nums.begin());
        for(int i = 0; i < n; ++i) {
            a = r;
            if( i < n-1 )
                a *= nums[i];
            if( i > 0 )
                a *= nums[i-1];
            mx = max(mx,a+_maxCoins(nums));
            if( i < n-1 ) {
                t = nums[i];
                nums[i] = r;
                r = t;
            }
        }
        nums.push_back(r);
        dp.insert({nums,mx});
        return mx;
    }

    // segment tree
    int t[2000];
    int combine(int a, int b) {
        int t = a*b;
        return a>b ? a+t : b+t;
    }

    void build(int a[], int v, int tl, int tr) {
        if( tl == tr ) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    int _maxCoins2(int v, int tl, int tr, int l, int r) {
        if( l > r )
            return 0;
        if( l == tl && r == tr )
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(_maxCoins2(v*2, tl, tm, l, min(r, tm)),
            _maxCoins2(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    int dp2[500][500];
    int * Nums;
    size_t N;

    int rec(int i, int j) {
        // idea:
        //   the kth ballon will burst at last in segment (i, j)
        //   divide the problem in (i, k-1) and (k+1, j) sub-segments.
        //   recursive function:
        //   solve(i, j) = max(solve(i, k-1) + solve(k+1, j) + nums[i-1] * nums[k] * nums[j+1])
        //     for all k where i<=k<=j.

        if( j < i ) return 0;
        if( dp2[i][j] != -1 ) return dp2[i][j];

        int t = 0;
        for(int k = i; k <= j; ++k) {
            int l = i == 0 ? 1 : Nums[i-1];
            int r = j == N-1 ? 1 : Nums[j+1];
            t = max(t,rec(i,k-1) + rec(k+1,j) + l * Nums[k] * r);
        }

        return dp2[i][j] = t;
    }

public:
    int maxCoins(vector<int>& nums) {
        N = nums.size();
        if( N == 0 ) return 0;
        if( N == 1 ) return nums[0];

        // TLE
        // return _maxCoins(nums);

        // gave up on segment tree solution

        // chain matrix multiplication
        Nums = nums.data();
        for(int i = 0; i < 500; ++i)
            for(int j = 0; j < 500; ++j)
                dp2[i][j] = -1;

        return rec(0,N-1);
    }
};
