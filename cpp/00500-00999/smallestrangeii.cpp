
// 910. Smallest Range II
// https://leetcode.com/problems/smallest-range-ii/
// day 21 Decemeber 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/571/week-3-december-15th-december-21st/3573/


class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        size_t n = A.size();
        if( n == 1 ) return 0;

        sort(begin(A), end(A));
        int mn = A[0];
        int mx = A[n-1];
        int d = mx - mn;
        if( K == 0 || K >= d ) return d;

        int ans = d;
        for (int i = 0; i <n - 1; ++i) {
            int a = A[i], b = A[i+1];
            int high = max(mx - K, a + K);
            int low = min(mn + K, b - K);
            ans = min(ans, high - low);
        }
        return ans;
    }
};
