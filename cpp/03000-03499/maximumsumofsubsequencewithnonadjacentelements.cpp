
// 3165. Maximum Sum of Subsequence With Non-adjacent Elements
// https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/



class Solution {
private:
    const long mod = 1000000007;

    int solve(vector<int>& nums, int n) {
        if( n == 1 )
            return max(0, nums[0]);
        if( n == 2 )
            return max({0, nums[0], nums[1]});


        // we have a choice
        //    not take OR
        //    take (just us OR us + 2 back)

        vector<long> mem(n);
        mem[0] = (long)nums[0];
        mem[1] = max((long)nums[0], (long)nums[1]);
        for(int i = 2; i < n; ++i) {

            long a = nums[i];
            long b = mem[i-1];
            long c = (mem[i-2] + nums[i]) % mod;

            mem[i] = max({a ,b ,c});
        }

        return mem[n-1];
    }

    vector<array<long,4>> t; // segment tree

    array<long,4> combine(array<long,4>& a, array<long,4>& b) {
        array<long,4> ret;

        // .xxxxxxxxxxxxxxx.
        // .xxxx. and Cxxxx.
        // .xxxx. and .xxxx.
        // .xxxxB and .xxxx.
        ret[0] = max({a[0] + b[2], a[0] + b[0], a[1] + b[0]});

        // .xxxxxxxxxxxxxxxD
        // .xxxx. and CxxxxD
        // .xxxx. and .xxxxD
        // .xxxxB and .xxxxD
        ret[1] = max({a[0] + b[3], a[0] + b[1], a[1] + b[1]});

        // Axxxxxxxxxxxxxxx.
        // Axxxx. and Cxxxx.
        // Axxxx. and .xxxx.
        // AxxxxB and .xxxx.
        ret[2] = max({a[2] + b[2], a[2] + b[0], a[3] + b[0]});

        // AxxxxxxxxxxxxxxxD
        // Axxxx. and CxxxxD
        // Axxxx. and .xxxxD
        // AxxxxB and .xxxxD
        ret[3] = max({a[2] + b[3], a[2] + b[1], a[3] + b[1]});

        return ret;
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v][0] = 0L;           // .xxxx. aka don't take
            t[v][1] = -1000000000L; // .xxxxB aka A...B-1, which does not make sense, hence we make it negativ
            t[v][2] = -1000000000L; // Axxxx. aka A-1...B, which does not make sense, hence we make it negativ
            t[v][3] = (long)a[tl];  // take
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    void update(int v, int tl, int tr, int pos, long new_val) {
        if (tl == tr) {
            t[v][0] = 0L;           // .xxxx. aka don't take
            t[v][1] = -1000000000L; // .xxxxB aka A...B-1, which does not make sense, hence we make it negativ
            t[v][2] = -1000000000L; // Axxxx. aka A-1...B, which does not make sense, hence we make it negativ
            t[v][3] = new_val;      // take
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, new_val);
            else
                update(v*2+1, tm+1, tr, pos, new_val);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int q_sz = queries.size();

        // if nums[i] < 0, we can set it to 0

        long ans = 0L;


        /*
        // brute force -> TLE
        for(int i = 0; i < q_sz; ++i) {
            nums[queries[i][0]] = queries[i][1];
            ans = (ans + max(0, solve(nums, n))) % mod;
        }
        */

        /* what can we combine?
         * let us say we have a range left A..B and a range right C..D
         * and we have calculate the max sum of a subsequence for every range in it
         * we can combine if we don't use adjacent elements
         * Axxxx. and CxxxxD
         * Axxxx. and Cxxxx.
         * Axxxx. and .xxxxD
         * Axxxx. and .xxxx.
         * -----------------
         * .xxxx. and CxxxxD
         * .xxxx. and Cxxxx.
         * .xxxx. and .xxxxD
         * .xxxx. and .xxxx.
         * -----------------
         * AxxxxB and .xxxxD
         * AxxxxB and .xxxx.
         * -----------------
         * .xxxxB and .xxxxD
         * .xxxxB and .xxxx.
         * so we need to track the max subsequences of a range if we
         * select or don't select the 1st element, select or don't select the last element
         * and we need to query that quickly
         * and we need to be able to modify the result as our array changes with every query
         * --> segment tree
         * each node needs to hold four stages
         * .xxx.   0
         * .xxxB   1
         * Axxx.   2
         * AxxxB   3
         */

        t.resize(4*n);
        build(nums, 1, 0, n-1);

        for(int i = 0; i < q_sz; ++i) {
            update(1, 0, n-1, queries[i][0], (long)queries[i][1]);
            // we would always ask for max subsequence sum of range 0..n-1
            // taking shortcut instead of implementing a get_max function on the tree
            // t[1] is the root of our segment tree
            ans = (ans + max({t[1][0], t[1][1], t[1][2], t[1][3]})) % mod;
        }

        return ans;
    }
};
