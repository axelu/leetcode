
// 3426. Manhattan Distances of All Arrangements of Pieces
// https://leetcode.com/problems/manhattan-distances-of-all-arrangements-of-pieces/





// solved the case for k = m*n
// was then trying to solve the case m == 1 || n == 1 (and k < n respectively k < m )
//     but got stuck
// knew needed to develop a formula
// great explanation here including proof:
//     https://leetcode.com/problems/manhattan-distances-of-all-arrangements-of-pieces/solutions/6299158/i-love-math
// used formula developed there



// initialize once; precompute factorial, modinverse, sum of integers, sum sum of integers
long intsum[100001];    // sum of integers 1 to i
long intsumsum[100001]; // sum of sum of integers 1 to i
long long factorial[100001];
long long inverse[100001];
bool init = false;

class Solution {
private:
    const long mod = 1000000007;

     long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,mod-2);
    }

    long long modCombinations(long long n, long long k) {
        return ((factorial[n] * inverse[k]) % mod * inverse[n-k]) % mod;
    }

    // modular division
    long modDivide(long a, long b) {
        // a = a % mod;
        long inv = modInverse(b);
        return (inv * a) % mod;
    }

public:
    int distanceSum(int m, int n, int k) {
        if( !init ) {
            init = true;
            intsum[0] = 0L;
            intsumsum[0] = 0L;
            factorial[0] = 1LL;
            inverse[0] = 1LL;
            for(long i = 1L; i <= 100000L; ++i) {
                intsum[i] = (intsum[i-1] + i) % mod;
                intsumsum[i] = (intsumsum[i-1] + intsum[i]) % mod;
                factorial[i] = (factorial[i-1] * i) % mod;
                inverse[i]   = modInverse(factorial[i]);
            }
        }

        // m rows
        // n cols
        // 1 <= m, n <= 1e5
        // 2 <= m * n <= 1e5
        // 2 <= k <= m * n

        // edge case k = m*n => only 1 arrangement is possible
        // manhattan distance between all cells in a grid
        if( k == m*n ) {
            if( m == 1 )
                return intsumsum[n-1];
            if( n == 1 )
                return intsumsum[m-1];

            // m != 1 and m != 1
            // by row
            // row distance of 1   m-1 times
            // row distance of 2   m-2 times
            // ...
            // row distance of m-1   1 time
            //
            // base row distance of 1
            long base = ((intsumsum[n] * 2L) % mod) - (long)n;
            if( base < 0 )
                base += mod;
            long ret = ((long)m * intsumsum[n-1]) % mod; // distances within all rows
            for(long rowdist = 1; rowdist <= (long)(m-1); ++rowdist) {
                ret = (ret + ((base * ((long)m-rowdist)) % mod)) %mod;
                // our base increases in each iteration
                base = (base + (((long long)n * (long long)n) % mod)) % mod;
            }
            return ret;
        }

        // ((m*n)-1 over k-2) * ((n*n)*m*((m*m)-1) + (m*m)*n*((n*n)-1))/6

        long M = m * n; // <= 100000
        long _comb = modCombinations(M-2, k-2); // cout << "_comb " << _comb << endl;
        // long tt1 = _comb * ((n*n)*m*((m*m)-1) + (m*m)*n*((n*n)-1))/6; // cout << "tt1 " << tt1 << endl;

        long m2 = ((long)m*(long)m) % mod; // cout << "m2 " << m2 << endl;
        long n2 = ((long)n*(long)n) % mod; // cout << "n2 " << n2 << endl;

        long a1 = (n2*(long)m) % mod;
        long a2 = m2 - 1L; if( a2 < 0 ) a2 += mod;
        long a  = (a1 * a2) % mod; // cout << "a " << a << endl;

        long b1 = (m2*(long)n) % mod;
        long b2 = n2-1L; if( b2 < 0 ) b2 += mod;
        long b  = (b1 * b2) % mod; // cout << "b " << b << endl;

        long c = (a+b) % mod; // cout << "c " << c << endl;
        long d = modDivide(c, 6L); // cout << "d " << d << endl;
        long e = (_comb * d) % mod;


        return e;
    }
};



/* attempt to solve

       if( m == 1 ) { // k < n

            // TODO mod

            long base = intsumsum[k-1];
            // we have a 'window' of length k  (n-k+1) times
            long f = n-k+1;
            // how many arrangements
            long _comb = 1L;
            long ret = (base * f) % mod; // base * f * _comb  <= _comb is 1
            // extend the window
            for(long i = k+1; i <= n; ++i) {
                // for each k-1 elements we made the distance larger by 1
                base = (base + (long)(k-1)) % mod;
                // how many 'windows' of this length i do we have?
                f = (n-i+1);
                // how many combinations do we have between 1st and last element?
                // example
                // xx**x 3
                _comb = modCombinations(i-2, k-2);

                ret = (ret + ((((base * f) % mod) * _comb) % mod)) % mod;
            }
            return ret;

        }
        if( n == 1 ) { // k < m

        }

 */
