
// 3356. Zero Array Transformation II
// https://leetcode.com/problems/zero-array-transformation-ii/





class Solution {
private:
    int t[400000];      // segment tree (max), lazy propagation, range addition, range query
    int lazy[400000];

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = max(t[v*2], t[v*2 + 1]);
        }
    }

    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    // range addition
    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = max(t[v*2], t[v*2+1]);
        }
    }

    // get max
    int query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INT_MIN;
        if (l == tl && tr == r)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(query(v*2, tl, tm, l, min(r, tm)),
                   query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        build(nums, 1, 0, n-1);
        if( query(1, 0, n-1, 0, n-1) <= 0 )
            return 0;

        for(int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int addend = -queries[i][2];

            update(1, 0, n-1, l, r, addend);
            if( query(1, 0, n-1, 0, n-1) <= 0 )
                return i+1;
        }

        return -1;
    }
};
