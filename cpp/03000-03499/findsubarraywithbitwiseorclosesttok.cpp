
// 3171. Find Subarray With Bitwise OR Closest to K
// https://leetcode.com/problems/find-subarray-with-bitwise-or-closest-to-k/







class Solution {
private:
    int t[400000]; // segment tree OR
    int n;

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] | t[v*2+1];
        }
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return get(v*2, tl, tm, l, min(r, tm)) | get(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    // binary search
    int lower_bound(int i, int s, int e, int target) {
        // i is our fix point
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int o = get(1, 0, n-1, i, mid);
        if( o == target ) {
            return mid;
        } else if( o > target ) {
            // can we do better?
            int t = lower_bound(i,s,mid-1,target);
            return t != -1 ? t : mid;
        } else {
            return lower_bound(i,mid+1,e,target);
        }
    }


public:
    int minimumDifference(vector<int>& nums, int k) {
        n = nums.size();

        build(nums, 1, 0, n-1);


        int ans = 1000000000;

        for(int i = 0; i < n; ++i) {

            int t = lower_bound(i,i,n-1,k); // cout << "i " << i << " t " << t << endl;
            if( t == -1 ) {
                // OR of range [i,n-1] < k
                ans = min(ans, k - get(1,0,n-1,i,n-1));
                continue;
            }

            int o = get(1,0,n-1,i,t);
            // o will be equal or greater k
            if( o == k )
                return 0; // we cannot do better

            // cout << "i " << i << " o greater " << o << endl;
            ans = min(ans, o-k);
            if( t > i && o > k ) {
                o = get(1,0,n-1,i,t-1);
                // cout << "i " << i << " o smaller " << o << endl;
                ans = min(ans, k-o);
            }
        }

        return ans;
    }
};
