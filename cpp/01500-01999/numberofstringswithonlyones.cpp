
// 1513. Number of Substrings With Only 1s
// https://leetcode.com/problems/number-of-substrings-with-only-1s/



class Solution {
public:
    int numSub(string s) {
        // 1 <= s.length <= 10^5
        // with that worse case scenario:
        // (n+1) * n/2 = (100000+1) * 100000/2 = 5000050000
        // integer overflow            INT_MAX = 2147483647

        long mod = 1000000007;
        long n = 0L;
        long ans = 0L;
        for(int i = 0; i < s.size(); ++i) {
            if( s[i] == '1' ) {
                ++n;
            } else {
                if( n > 0L ) {
                    ans += ((n+1) * n/2) % mod;
                    n = 0L;
                }
            }
        }
        // finish up
        if( n > 0L )
            ans += ((n+1) * n/2) % mod;


        return ans;
    }
};
