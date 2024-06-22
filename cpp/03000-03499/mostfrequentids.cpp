
// 3092. Most Frequent IDs
// https://leetcode.com/problems/most-frequent-ids/





class Solution {
private:
    vector<long long> t; // segment tree memory efficient indexing

    void update(int v, int tl, int tr, int pos, long delta) {
        if (tl == tr) {
            t[v] += delta;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, delta);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, delta);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }


public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        unordered_map<int,int> um;
        int n = 0;
        for(int i: nums) {
            auto p = um.insert({i,n});
            if( p.second )
                ++n;
        }

        t.assign(2*n,0);

        int nums_sz = nums.size(); // nums.size() == freq.size()
        vector<long long> ans(nums_sz);
        for(int i = 0; i < nums_sz; ++i) {

            int pos = um[nums[i]];
            update(1, 0, n - 1, pos, freq[i]);
            ans[i] = t[1]; // get_max in range [0,n-1]
        }


        return ans;
    }
};
