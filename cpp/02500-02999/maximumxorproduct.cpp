
// 2939. Maximum Xor Product
// https://leetcode.com/problems/maximum-xor-product/





// all about XOR https://accu.org/journals/overload/20/109/lewin_1915/

class Solution {
private:
    const long mod = 1000000007;

    vector<bool> to_binary(long long x) {
        vector<bool> ret(50,false);
        int i = 49;
        while( x ) {
            if( x & 1LL )
                ret[i] = true;
            x >>= 1;
            --i;
        }
        return ret;
    }

public:
    int maximumXorProduct(long long a, long long b, int n) {
        // 0 <= a, b < 2^50
        // 0 <= n <= 50
        //      2^50 =    1125899906842624
        // LLONG_MAX = 9223372036854775807

        /*
        long long n_sz = pow(2,n);
        for(long long i = 0; i < n_sz; ++i) {
            long long _a = (long long)a ^ i;
            long long _b = (long long)b ^ i;

            // TODO mod
            long long r = _a * _b;

            printf("x %i a %i b %i c %i\n", i, _a, _b, r);
        }
        return 99;
        */

        // observation
        //    we achive max if
        //      if at a given binary position a AND b have a set bit, x is unset
        //      if at a given binary position a AND b have unset bit, x is set
        //      the question becomes: what if a is set and be is unset or vice versa?
        //      if we go from right to left, we set bit in x on the so far smaller one

        // handle n == 0 -> answer is a * b
        if( n == 0 )
            return ((a % mod) * (b % mod)) % mod;

        long long x = 0LL;

        if( a == b ) {
            for(int i = n-1; i >= 0; --i) {
                long long mask = 1LL << i;
                if( !(a & mask) )
                    x |= mask;
            }

        } else {
            long long ta = 0LL;
            long long tb = 0LL;
            for(int i = 49; i >= 0; --i) {
                long long mask = 1LL << i;
                if( i > n-1 ) {
                    if( a & mask )
                        ta |= mask;
                    if( b & mask )
                        tb |= mask;
                } else {
                    if( (a & mask) && (b & mask) ) {
                        // do nothing
                    } else if( !(a & mask) && !(b & mask) ) {
                        x |= mask;
                    } else {
                        if( ta < tb ) {
                            if( !(a & mask) )
                                x |= mask;
                            ta |= mask;
                        } else {
                            if( !(b & mask) )
                                x |= mask;
                            tb |= mask;
                        }
                    }
                }
            }
        }
        // cout << "x " << x << endl;

        long long _a = a ^ x;
        long long _b = b ^ x;
        return ((_a % mod) * (_b % mod)) % mod;
    }
};
