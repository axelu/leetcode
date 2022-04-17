
// 1526. Minimum Number of Increments on Subarrays to Form a Target Array
// https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/



// inspired by https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-8

class Solution {
private:
    int * t; // segment tree holding index of min element in range

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = tl;
        } else {
            int mid = (tl + tr) / 2;
            build(a, v*2, tl, mid);
            build(a, v*2+1, mid+1, tr);
            t[v] = a[t[v*2]] <= a[t[v*2+1]] ? t[v*2] : t[v*2+1];
        }
    }

    int get_min_idx(int a[], int v, int tl, int tr, int l, int r) {
        // returns index of min element in a[l,r] inclusive

        if (l > r)
            return -1; // bad index
        if (l == tl && r == tr)
            return t[v];

        int mid = (tl + tr) / 2;

        if( r <= mid)     // query falls in left subtree
            return get_min_idx(a,v*2,tl,mid,l,r);
        else if( l > mid) // query falls in right subtree
            return get_min_idx(a,v*2+1,mid+1,tr,l,r);

        // query covers the mid point
        // get answer for [l,mid]
        int lmin = get_min_idx(a,v*2,tl,mid,l,mid);
        // get answer for [mid+1,r]
        int rmin = get_min_idx(a,v*2+1,mid+1,tr,mid+1,r);

        if( lmin == -1 )
            return rmin;
        if( rmin == -1 )
            return lmin;

        return a[lmin] <= a[rmin] ? lmin : rmin;
    }

    int rec(int a[], int n, int l, int r, int curr) {
        if( l > r )
            return 0;

        int mn_idx = get_min_idx(a,1,0,n-1,l,r);

        // we can increase the range [l,r] from curr to a[mn_idx];
        int ret = a[mn_idx] - curr;

        // now we need to increase the left side on mn_idx and right side of mn_idx
        ret += rec(a,n,l,mn_idx-1,a[mn_idx]);
        ret += rec(a,n,mn_idx+1,r,a[mn_idx]);

        return ret;
    }

public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size();

        // idea:
        // build a segment tree to answer min range query
        // the tree will store the min element index
        // we can increase to that min element and then
        // repeat for the left side of that min element and for the
        // right side of that min element to get our answer

        // build a segment tree
        int T[4*n];
        t = T;
        build(target.data(),1,0,n-1);

        // we start with an array of all 0s
        return rec(target.data(),n,0,n-1,0);

    }
};
