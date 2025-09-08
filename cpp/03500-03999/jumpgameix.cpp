
// 3660. Jump Game IX
// https://leetcode.com/problems/jump-game-ix/




class Solution {
private:
    // idx to the left holding max if gt value at current pos, else -1
    int mx2lft[100000];
    // right most idx to the right holding a value lt value at current pos,
    // else -1
    int mn2rgt[100000];


    int t[200000]; // segment tree, memory efficient implementation, max range query, point update

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    int get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return -1;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    int rec(vector<int>& nums, int i, vector<int>& ans) {
        // cout << "rec i " << i << endl;
        if( ans[i] != -1 )
            return ans[i];

        int ret = nums[i];
        if( mx2lft[i] != -1 ) {
            // we know whatever it points to is larger already
            ret = nums[mx2lft[i]];
            // avoid endless loop
            if( mn2rgt[mx2lft[i]] != i )
                ret = max(ret, rec(nums, mx2lft[i], ans));
        }
        if( mn2rgt[i] != -1 ) {
            ret = max(ret, rec(nums, mn2rgt[i], ans));
        }
        return ans[i] = ret;
    }

public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();

        // pre-process

        // index to our left holding max value seen so far
        // if that max value seen so far > value at our current pos
        int mx2lftval = -1;
        int mx2lftidx = -1;
        for(int i = 0; i < n; ++i) {
            mx2lft[i] = mx2lftval > nums[i] ? mx2lftidx : -1;
            if( nums[i] > mx2lftval ) {
                mx2lftval = nums[i];
                mx2lftidx = i;
            }
        }

        // compression
        set<int> st;
        for(int x: nums)
            st.insert(x);
        map<int,int> dict;
        int idx = 0;
        for(int x: st)
            dict[x] = idx++;

        int unique_cnt = idx;

        memset(mn2rgt, -1, sizeof mn2rgt);

        // let i be our current pos in nums
        // let x = nums[i]
        // we can jump to
        //     any pos j < 1 to our left where nums[j] > x
        //     so we will blindly look for the max to our left (including us)
        //     once we have that max, we can however use that max
        //     to jump to the rightmost j where nums[j] < max to our our left
        //     and with that we have additionally access to the max
        //     right of us up to the index j

        // segment tree holding the right most index
        // of each unique number in nums
        // our leafs are those unique numbers ordered asc
        // we initialize with -1, basically not having seen any
        memset(t, -1, sizeof t);
        bool seen[100000]; memset(seen, false, sizeof seen);

        // going right to left
        // update our tree with what we have seen
        idx = dict[nums[n-1]]; // it is guaranteed the x is in our map
        update(1, 0, unique_cnt - 1, idx, n-1);
        seen[idx] = true;

        for(int i = n-2; i >= 0; --i) {
            // we can reach all values to the left of i including us
            int mxl = nums[i];
            if( mx2lft[i] != -1 ) {
                mxl = nums[mx2lft[i]];
            }

            // but we can also reach values to the right of i
            // up to the rightmost index in nums holding a value
            // smaller than mxl
            // what is the right most index in nums holding a value
            // smaller than mxl?
            idx = dict[mxl];
            if( idx > 0 )
                mn2rgt[i] = get_max(1, 0, unique_cnt-1, 0, idx-1);

            // update our t2
            idx = dict[nums[i]];
            if( !seen[idx] ) {
                update(1, 0, unique_cnt - 1, idx, i);
                seen[idx] = true;
            }
        }

        vector<int> ans(n, -1);
        for(int i = 0; i < n; ++i) {
            if( ans[i] == -1 )
                rec(nums, i, ans);

        }

        return ans;
    }
};
