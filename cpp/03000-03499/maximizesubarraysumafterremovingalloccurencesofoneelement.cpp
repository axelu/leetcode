
// 3410. Maximize Subarray Sum After Removing All Occurrences of One Element
// https://leetcode.com/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/





class Solution {
private:
    struct T {
        long long sum;
        long long max_subarray_sum;
        long long max_prefix_sum;
        long long max_suffix_sum;
        T() : sum(0), max_subarray_sum(0), max_prefix_sum(0), max_suffix_sum(0) {}
        T(int x) : sum(x), max_subarray_sum(x), max_prefix_sum(x), max_suffix_sum(x) {}
    };

    vector<T> t; // segment tree memory efficient indexing

    T combine(T& a, T& b) {
        T ret(-1);

        ret.sum = a.sum + b.sum;
        ret.max_prefix_sum = max(a.max_prefix_sum, a.sum + b.max_prefix_sum);
        ret.max_suffix_sum = max(b.max_suffix_sum, a.max_suffix_sum + b.sum);
        ret.max_subarray_sum = max({a.max_subarray_sum, b.max_subarray_sum,
                                    a.max_suffix_sum + b.max_prefix_sum});

        return ret;
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = T(a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    void update(int v, int tl, int tr, int pos, long long new_val) {
        if (tl == tr) {
            t[v].sum = new_val;
            t[v].max_subarray_sum = new_val;
            t[v].max_prefix_sum = new_val;
            t[v].max_suffix_sum = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

public:
    long long maxSubarraySum(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0;

        map<int, vector<int>> positions;
        for(int i = 0; i < n; ++i) {
            positions[nums[i]].push_back(i);
            ans += (long long)nums[i];
        }

        if( positions.begin()->first >= 0 ) {
            // there are only non-negative numbers in nums
            return ans;
        }
        if( positions.rbegin()->first < 0 ) {
            return positions.rbegin()->first;
        }

        t.resize(2*n);
        build(nums, 1, 0, n-1);

        for(auto it = positions.begin(); it != positions.end() && it->first < 0; ++it) {
            // TODO what if we don't use pointers in the tree.
            // we could copy the tree array, and then simply restore,
            // which maybe faster than reversing the update
            for(int pos: it->second)
                update(1, 0, n-1, pos, 0LL);
            ans = max(ans, t[1].max_subarray_sum);
            for(int pos: it->second)
                update(1, 0, n-1, pos, (long long)it->first);
        }

        return ans;
    }
};
