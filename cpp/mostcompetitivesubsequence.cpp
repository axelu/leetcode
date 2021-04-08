
// 1673. Find the Most Competitive Subsequence
// https://leetcode.com/problems/find-the-most-competitive-subsequence/


class Solution {
// inspired by https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-8
private:
    pair<int, int> * t;

    pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
        if (a.first < b.first)
            return a;
        if (b.first < a.first)
            return b;
        return make_pair(a.first, min(a.second,b.second));
    }

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = make_pair(a[tl], tl);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    pair<int, int> get_min(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return make_pair(INT_MAX, 0);
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(get_min(v*2, tl, tm, l, min(r, tm)),
            get_min(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        size_t n = nums.size();
        // base cases
        if( n == 1 ) return {nums[0]};
        if( k == 1 ) return {*min_element(nums.begin(),nums.end())};
        if( k == n ) return nums;

        // Idea: get minimum and its leftmost position l in range [0,n-k], then
        //       get minimum and its leftmost position l in range [l+1,n-k+1], and so on.

        // segment tree that returns minimum in given interval and
        // leftmost position of given minimum in said interval
        pair<int, int>  T[4*n];
        t = T;
        build(nums.data(),1,0,n-1);

        vector<int> ans(k);
        pair<int, int> p;
        int l = 0, i = 0;
        for(int r = n-k; r < n; ++r) {
            p = get_min(1,0,n-1,l,r);
            ans[i] = p.first;
            ++i;
            l = p.second + 1;
        }
        return ans;
    }
};
