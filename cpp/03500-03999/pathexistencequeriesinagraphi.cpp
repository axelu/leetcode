
// 3532. Path Existence Queries in a Graph I
// https://leetcode.com/problems/path-existence-queries-in-a-graph-i/




class Solution {
private:
    int t[400000]; // segment tree, range query for max

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = max(t[v*2], t[v*2+1]);
        }
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get(v*2, tl, tm, l, min(r, tm)),
                       get(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    // binary search
    int lower_bound(vector<int>& nums, int target) {
        int n = nums.size();

        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        if( n == 1 )
            return vector<bool>(queries.size(),true);

        // plot the unique values on a value line
        // then we can see if we can jump

        set<int> unique_st;
        for(int x: nums)
            unique_st.insert(x);

        if( unique_st.size() == 1 )
            return vector<bool>(queries.size(),true);


        vector<int> values(unique_st.size());
        int val_idx = 0;
        for(int x: unique_st)
            values[val_idx++] = x;

        /*
        for(int i = 0; i < val_idx; ++i)
            cout << i << ":" << values[i] << " ";
        cout << endl;
        */

        vector<int> diffs(val_idx - 1);
        for(int i = 0; i < val_idx - 1; ++i)
            diffs[i] = values[i+1] - values[i];

        build(diffs, 1, 0, val_idx - 2);

        int q_sz = queries.size();
        vector<bool> ans(q_sz, false);
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int u_val = nums[u];

            int v = queries[i][1];
            int v_val = nums[v];

            if( v_val < u_val )
                swap(u_val, v_val);

            int u_val_idx = lower_bound(values, u_val);
            int v_val_idx = lower_bound(values, v_val);

            int t = get(1, 0, val_idx - 2, u_val_idx, v_val_idx - 1);
            if( t <= maxDiff)
                ans[i] = true;
        }

        return ans;
    }
};
