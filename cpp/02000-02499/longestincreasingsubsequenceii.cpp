
// 2407. Longest Increasing Subsequence II
// https://leetcode.com/problems/longest-increasing-subsequence-ii/





class Solution {
private:
    vector<int> t; // segment tree memory efficient indexing

    int get_max(int v, int tl, int tr, int l, int r) {
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
    int lengthOfLIS(vector<int>& nums, int k) {
        int nums_sz = nums.size();
        if( nums_sz == 1 )
            return 1;

        set<int> unique;
        for(int val: nums)
            unique.insert(val);
        int n = 0;
        map<int,int> mp; // val, idx
        for(int val: unique)
            mp.insert({val, n++});

        t.assign(2 * n, 0);
        int pos = mp[nums[nums_sz - 1]];
        update(1, 0, n-1, pos, 1);

        int ans = 1;

        for(int i = nums_sz - 2; i >= 0; --i) {
            int val = nums[i];
            int a = 0;
            auto lo_it = mp.upper_bound(val);
            if( lo_it != mp.end() && lo_it->first <= val + k ) {

                auto hi_it = mp.lower_bound(val + k);
                if( hi_it == mp.end() || hi_it->first > val + k )
                    hi_it = prev(hi_it);

                int lo_idx = lo_it->second;
                int hi_idx = hi_it->second;
                a = get_max(1, 0, n-1, lo_idx, hi_idx);
            }
            ans = max(ans, 1 + a);
            pos = mp[nums[i]];
            update(1, 0, n-1, pos, 1 + a);
        }

        return ans;
    }
};
