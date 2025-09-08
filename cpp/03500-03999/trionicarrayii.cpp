
// 3640. Trionic Array II
// https://leetcode.com/problems/trionic-array-ii/





class Solution {
private:
    // array<long long, 4> 0: left val, 1: right val, 2: strictly increasing 1 yes 0 no, 3: sum
    array<long long, 4> t[400000]; // segment tree, range query

    array<long long, 4> combine(array<long long, 4>& a, array<long long, 4>& b) {
        if( a[2] == -1LL )
            return b;
        if( b[2] == -1 )
            return a;

        array<long long, 4> ret;
        ret[0] = a[0];
        ret[1] = b[1];
        ret[2] = a[2] & b[2];
        ret[3] = a[3] + b[3];
        return ret;
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v][0] = (long long)a[tl];
            t[v][1] = (long long)a[tl];
            t[v][2] = 1LL;
            t[v][3] = (long long)a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    array<long long, 4> get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {-1,-1,-1,-1};
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        auto lft = get(v*2, tl, tm, l, min(r, tm));
        auto rgt = get(v*2+1, tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }

    long long get_max_sum_leg1(vector<int>& nums, int i) {
        long long sum = (long long)nums[i];
        long long ret = sum;
        while( i-1 >= 0 && nums[i-1] < nums[i] ) {
            --i;
            sum += (long long)nums[i];
            ret = max(ret, sum);
        }

        return ret;
    }

    long long get_max_sum_leg3(vector<int>& nums, int i) {
        int n = nums.size();
        long long sum = (long long)nums[i];
        long long ret = sum;
        while( i+1 < n && nums[i] < nums[i+1] ) {
            ++i;
            sum += (long long)nums[i];
            ret = max(ret, sum);
        }

        return ret;
    }


public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size(); // 4 <= n <= 1e5
        // it is guaranteed that at least one trionic subarray exists
        if( n == 4 ) {
            long long ret = 0LL;
            for(long long x: nums)
                ret += x;
            return ret;
        }

        // l < p < q < r with 0 <= l < r < n

        // if we identify each second leg p..q, that has a fixed sum
        // then we can find then max sum 1st leg and
        // max sum third leg

        // 0 < p < n-2 => pmin = 1, pmax = n-3
        // 1 < q < n-1 => qmin = 2, qmax = n-2

        vector<int> ps; // peak indices aka indices where nums[ps[i-1]] < nums[ps[i]] > nums[ps[i+1]]
        for(int i = 1; i <= n-3; ++i)
            if( nums[i-1] < nums[i] && nums[i] > nums[i+1] )
                ps.push_back(i);

        vector<int> qs; // valey indices aka indices where nums[ps[i-1]] > nums[ps[i]] < nums[ps[i+1]]
        for(int i = 2; i <= n-2; ++i)
            if( nums[i-1] > nums[i] && nums[i] < nums[i+1] )
                qs.push_back(i);

        build(nums, 1, 0, n-1);

        long long ans = LLONG_MIN;

        int ps_sz = ps.size();
        int qs_sz = qs.size();
        int j = 0;                                    // index in qs
        for(int i = 0; i < ps_sz && j < qs_sz; ++i) { // index in ps
            int p = ps[i];
            // get q
            int q = -1;
            for(; j < qs_sz; ++j) {
                if( qs[j] > p ) {
                    q = qs[j];
                    break;
                }
            }
            if( q != -1 ) {
                // nums[p], nums[p+1], ... , nums[q-1], nums[q]
                // must be strictly increasing
                auto arr = get(1, 0, n-1, p, q);
                if( arr[2] != 1LL )
                    continue;

                long long sum_leg2 = arr[3];

                // TODO make this faster !!!
                // leg1
                // we know we can go to the left from p-1
                // we can go as long as it is strictly 'increasing',
                // aka when we go right to left strictly decreasing
                // we need to find the maximum sum along the way
                // leg3
                // same applies to leg3 starting from q+1 going right

                long long sum_leg1 = get_max_sum_leg1(nums, p-1);

                long long sum_leg3 = get_max_sum_leg3(nums, q+1);

                ans = max(ans, sum_leg1 + sum_leg2 + sum_leg3);
            }
        }

        return ans;
    }
};
