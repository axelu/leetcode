
// 2550. Count Collisions of Monkeys on a Polygon
// https://leetcode.com/problems/count-collisions-of-monkeys-on-a-polygon/





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
    int monkeyMove(int n) {
        long ans = modular_pow(2,n) - 2;
        if( ans < 0 )
            ans += mod;

        return ans;
    }
};
