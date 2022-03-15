
// 634. Find the Derangement of An Array
// https://leetcode.com/problems/find-the-derangement-of-an-array/

// https://en.wikipedia.org/wiki/Derangement
class Solution {
public:
    int findDerangement(int n) {

        // according to Wikipedia
        // derangement !n
        // !n = (n-1) * (!(n-1) + !(n-2)) for n ≥ 2
        // where where !0 = 1 and !1 = 0

        if( n == 1 )
            return 0;

        long mod = 1000000007;

        long m2 = 1;
        long m1 = 0;
        long m;
        for(int i = 2; i <= n; ++i) {
            m =  ((i-1) * ((m1 + m2) % mod)) % mod;

            m2 = m1;
            m1 = m;
        }

        return m1;
    }
};
