
// 3007. Maximum Number That Sum of the Prices Is Less Than or Equal to K
// https://leetcode.com/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k/





class Solution {
private:

    int leftmostbit(long long x) {
        // x > 0
        int ret;
        for(int i = 63; ; --i)
            if( (x >> i) & 1LL )
                return i;

        return -1;
    }

    long long get_sum_prices(long long n, int x) {

        int lmb = leftmostbit(n);

        long long ret = 0LL;

        // we will be at each bit n+1 times
        for(int k = lmb; k >= 0; --k) {
            int i = k + 1;
            if( i % x )
                continue;

            long long t = pow(2,k);
            long long d = (n+1) / t;
            long long rem = (n+1) % t;

            if( d % 2LL == 0LL ) {
                ret += d/2LL * t;
            } else {
                ret += ((d-1)/2LL * t) + rem;
            }
        }

        return ret;
    }

    long long search(long long s, long long e, long long target, long long x) {
        if( s > e )
            return -1LL;

        long long mid = s + ((e-s)/2LL);
        long long res = get_sum_prices(mid, x);
        if( res <= target ) {
            // can we do better?
            long long t = search(mid+1, e, target, x);
            return t != -1LL ? t : mid;
        }

        return search(s, mid-1, target, x);
    }

public:
    long long findMaximumNumber(long long k, int x) {
        // 1 <= k <= 1e15
        return search(1LL, 1e15, k, x);
    }
};
