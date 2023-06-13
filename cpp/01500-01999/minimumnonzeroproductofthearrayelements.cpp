
// 1969. Minimum Non-Zero Product of the Array Elements
// https://leetcode.com/problems/minimum-non-zero-product-of-the-array-elements/





/* example p = 5
 * 2^p - 1 = 31
 *             43210
 * 31 binary   11111
 * with that we have 15 0s in every bit position and 16 1s in every bit position
 * we can rearange those so that we get 15 1s, 15 30s and one 31, which will yield
 * the smallest product
 *
 */
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

            // base = (base * base) % mod;
            base = ((base % mod) * (base % mod)) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }

public:
    int minNonZeroProduct(int p) {
        // 1 <= p <= 60                                      9223372036854775807  long long max
        // 1-indexed array inclusive range [1, 2^p-1] -> [1, 1152921504606846975]
        // upper end binary is 60 1s 111111111111111111111111111111111111111111111111111111111111

        long b = pow(2,p);
        b = b - 1L;

        long a = modular_pow(b-1,b/2);
        long c = (a * (b % mod)) % mod;

        return c;
    }
};
