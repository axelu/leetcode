
// 3152. Special Array II
// https://leetcode.com/problems/special-array-ii/






class Solution {
private:
    struct T {
        int l;
        int r;
        bool is_special;
        T(int l, int r, bool is_special) : l(l), r(r), is_special(is_special) {}
    };

    T * t[200000]; // segment tree memory efficient indexing

    T * combine(T * a, T * b) {
        // a left
        // b right
        if( !a->is_special || !b->is_special || ( a->r != -1 && b->l != -1 && a->r % 2 == b->l % 2) )
            return new T(-1, -1, false);

        return new T(a->l, b->r, true);
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = new T(a[tl], a[tl], true);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    T * get(int v, int tl, int tr, int l, int r) {
        if( l > r )
            return new T(-1, -1, true);
        if( l == tl && r == tr )
            return t[v];

        int tm = (tl + tr) / 2;
        T * lft = get(v+1, tl, tm, l, min(r, tm));
        T * rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }

public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        build(nums, 1, 0, n-1);

        int q_sz = queries.size();
        vector<bool> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            T * a = get(1, 0, n-1, queries[i][0], queries[i][1]);
            ans[i] = a->is_special;
        }

        return ans;
    }
};
