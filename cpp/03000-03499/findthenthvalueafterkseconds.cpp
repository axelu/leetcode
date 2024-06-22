
// 3179. Find the N-th Value After K Seconds
// https://leetcode.com/problems/find-the-n-th-value-after-k-seconds/



class Solution {
public:
    int valueAfterKSeconds(int n, int k) {
        // 1 <= n, k <= 1000

        // edge cases
        if( n == 1 )
            return 1;
        if( k == 1 )
            return n;

        const long mod = 1000000007;

        // brute force

        int d_sz = n-1;


        long _pre[d_sz];
        for(int j = 0; j < d_sz; ++j)
            _pre[j] = 1L;
        long * pre = _pre;

        long _cur[d_sz];
        long * cur = _cur;

        for(int i = 2; i <= k; ++i) {
            cur[0] = i;
            for(int j = 1; j < d_sz; ++j)
                cur[j] = (cur[j-1] + pre[j]) % mod;

            swap(pre, cur);
        }

        long a = 1L;
        for(int j = 0; j < d_sz; ++j)
            a = (a + pre[j]) % mod;

        return a;
    }
};
