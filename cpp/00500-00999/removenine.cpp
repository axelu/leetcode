
// 660. Remove 9
// https://leetcode.com/problems/remove-9/




class Solution {
public:
    int newInteger(int n) {
        // 1 <= n <= 8 * 1e8
        if( n < 9 )
            return n;

        // base 9 encoding
        int ans = 0;
        long f = 1;
        int rem;
        while( n > 0 ) {
            rem = n % 9;
            ans = rem * f + ans;
            n /= 9;
            f *= 10;
        }

        return ans;
    }
};
