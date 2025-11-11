
// 3726. Remove Zeros in Decimal Representation
// https://leetcode.com/problems/remove-zeros-in-decimal-representation/


class Solution {
public:
    long long removeZeros(long long n) {
        long long ans = 0LL;

        long long f = 1LL;
        while( n ) {
            long long rem = n % 10LL;
            if( rem != 0LL ) {
                ans += f * rem;
                f *= 10LL;
            }
            n /= 10LL;
        }

        return ans;
    }
};
