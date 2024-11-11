
// 3255. Find the Power of K-Size Subarrays II
// https://leetcode.com/problems/find-the-power-of-k-size-subarrays-ii/





class Solution {
private:
    array<int,3> t[400000]; // consecutive, left (min), right (max)

    array<int,3> combine(array<int,3> a, array<int,3> b) {
        if( a[0] == -1 )
            return b;
        if( b[0] == -1 )
            return a;

        if( a[0] == 0 || b[0] == 0 )
            return {0, a[1], b[2]};

        int consecutive = a[2] + 1 == b[1] ? 1 : 0;
        return {consecutive, a[1], b[2]};
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {1, a[tl], a[tl]};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    array<int,3> get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return {-1, -1, -1};
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(get_max(v*2, tl, tm, l, min(r, tm)),
                       get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size();

        build(nums, 1, 0, n-1);

        vector<int> ans;
        for(int i = 0; i <= n-k; ++i) {
            int j = i+k-1;

            auto a = get_max(1, 0, n-1, i, j);
            if( a[0] )
                ans.push_back(nums[j]);
            else
                ans.push_back(-1);
        }

        return ans;
    }
};
