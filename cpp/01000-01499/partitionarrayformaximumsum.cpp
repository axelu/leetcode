
// 1043. Partition Array for Maximum Sum
// https://leetcode.com/problems/partition-array-for-maximum-sum/





class Solution {
private:
// inspired by https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-8
    int * t;

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = max(t[v*2],t[v*2+1]);
        }
    }

    int get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return -1;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return max(get_max(v*2, tl, tm, l, min(r, tm)),
            get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        // 1 <= arr.length <= 500
        // 0 <= arr[i] <= 10^9
        // 1 <= k <= arr.length

        // worst case scenario:
        // arr.length = 500
        // arr[0] = arr[1] = ... = arr[499] = 10^9
        // k = 500
        // -> 500 * 10^9 = 500000000000
        //       INT_MAX =   2147483647   we have integer overflow 500000000000 > 2147483647

        // from the question:
        // Think dynamic programming: dp[i] will be the answer for array A[0], ..., A[i-1].
        // For j = 1 .. k that keeps everything in bounds, dp[i] is the maximum of dp[i-j] + max(A[i-1], ..., A[i-j]) * j .

        int n = arr.size();

        // build a segment tree
        int T[4*n];
        t = T;
        build(arr.data(),1,0,n-1);

        long dp[n+1];memset(dp,0,sizeof dp);

        for(int i = 1; i <= n; ++i) {

            long res = 0;
            for(int j = 1; j <= k; ++j) {
                if( j > i ) break;
                res = max(res,dp[i-j] + (long)get_max(1,0,n-1,i-j,i-1)*j);
            }

            dp[i] = res;

        }

        return dp[n];
    }
};
