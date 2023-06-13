
// 1922. Count Good Numbers
// https://leetcode.com/problems/count-good-numbers/


class Solution {
private:
    long mod = 1000000007;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }


public:
    int countGoodNumbers(long long n) {
        if( n == 1 )
            return 5;

        long exponent = n / 2L;

        long ans = modular_pow(20,exponent);
        if( n % 2L )
            ans = (ans * 5L) % mod;

        return ans;
    }
};
