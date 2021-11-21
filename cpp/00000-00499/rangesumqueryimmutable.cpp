
// 303. Range Sum Query - Immutable
// https://leetcode.com/problems/range-sum-query-immutable/

// https://cp-algorithms.com/data_structures/segment_tree.html
class NumArray {
private:
    int n;
    int t[40000]; // segment tree

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    int sum(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return sum(v*2, tl, tm, l, min(r, tm))
               + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        if( n > 0 )
            build(nums.data(),1,0,n-1);
    }

    int sumRange(int i, int j) {
        return n == 0 ? 0 : sum(1,0,n-1,i,j);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
