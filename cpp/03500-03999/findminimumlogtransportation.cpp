
// 3560. Find Minimum Log Transportation Cost
// https://leetcode.com/problems/find-minimum-log-transportation-cost/

class Solution {
private:
    long long solve(int n, int k) {
        // n > k

        long long ret = LLONG_MAX;

        long long len1 = k;
        long long len2 = n - k;

        while( len2 <= k ) {
            ret = min(ret, len1 * len2);
            --len1;
            ++len2;
        }

        return ret;
    }

public:
    long long minCuttingCost(int n, int m, int k) {
        // it is guaranteed that it is always possible to transport the logs.

        if( n <= k && m <= k )
            return 0LL;

        // only n or m will be greater k
        if( n > k )
            return solve(n, k);
        else
            return solve(m, k);
    }
};
