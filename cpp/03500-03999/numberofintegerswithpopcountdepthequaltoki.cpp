
// 3621. Number of Integers With Popcount-Depth Equal to K I
// https://leetcode.com/problems/number-of-integers-with-popcount-depth-equal-to-k-i/




// initialize once
bool init = false;
int _popcountDepth[52];
// combinations precompuate via Pascal's triangle
long long nCk[51][51];


class Solution {
private:
    int findRightMostSetBit(long long x) {
        // it is guaranteed that x > 0
        int ret = 0;
        x = x >> 1;
        while( x ) {
            ++ret;
            x = x >> 1;
        }
        return ret;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int rec(int i) {
        if( _popcountDepth[i] != -1 )
            return _popcountDepth[i];

        int setbits = countSetBits(i);
        return _popcountDepth[i] = 1 + rec(setbits);
    }

    // Returns factorial of n
    long long fact(int n) {
        long long res = 1;
        for (int i = 2; i <= n; i++)
            res = res * (long long)i;
        return res;
    }

    long long nCr(int n, int r) {
        cout << "nCr n " << n << " r " << r << endl;
        return fact(n) / (fact(r) * fact(n - r));
    }

    long long n;
    int right_most_set_bit;

    long long rec(long long x, int pos, int k) {
        // cout << "rec x " << x << " pos " << pos << " k " << k << endl;

        // k how many bits we can still set

        if( x > n )
            return 0LL;
        if( k == 0 )
            return 1LL;
        if( pos > right_most_set_bit )
            return 0LL;

        // we have a choice
        //     don't set the bit at pos OR
        //     set the bit at pos

        long long ret = rec(x, pos+1, k);

        x |= (1LL<<pos);
        ret += rec(x, pos+1, k-1);

        return ret;
    }

public:
    long long popcountDepth(long long n, int k) {
        // constraints
        //     1 <= n <= 1e15
        //     1e15 decimal 1000000000000000
        //          binary  11100011010111111010100100110001101000000000000000 (50digits)
        //          decimal  562949953421311
        //          binary  01111111111111111111111111111111111111111111111111
        //     0 <= k <= 5

        /*
           x
         with
           b
        setbits
           1    ->  1
           2    ->  2(b 1) -> 1                              popcountDepth = 2
           3    ->  3(b 2) -> 2(b 1) -> 1                    popcountDepth = 3
           4    ->  4(b 1) -> 1                              popcountDepth = 2
           5    ->  5(b 2) -> 2(b 1) -> 1                    popcountDepth = 3
           6    ->  6(b 2) -> 2(b 1) -> 1                    popcountDepth = 3
           7    ->  7(b 3) -> 3(b 2) -> 2(b 1) -> 1          popcountDepth = 4
           8    ->  8(b 1) -> 1                              popcountDepth = 2
           9    ->  9(b 2) -> 2(b 1) -> 1                    popcountDeppt = 3
           ...
          48    -> 48(b 2) -> 2(b 1) -> 1                    popcountDepth = 3
          49    -> 49(b 3) -> 3(b 2) -> 2(b 1) -> 1          popcountDepth = 4
          50    -> 50(b 3) -> 3(b 2) -> 2(b 1) -> 1          popcountDepth = 4
        */

        if( !init ) {
            init = true;

            memset(_popcountDepth,-1,sizeof _popcountDepth);
            _popcountDepth[1] = 1;
            for(int i = 2; i <= 51; ++i) {
                rec(i);
                // cout << "set bits " << i << " popcountDepth " << _popcountDepth[i] << endl;
            }

            for(int i = 0; i <= 50; ++i) {
                nCk[i][0] = 1;
                nCk[i][i] = 1;
            }
            for(int i = 2; i <= 50; ++i) {
                for(int j = 1; j < 50; ++j) {
                    nCk[i][j] = (nCk[i-1][j] + nCk[i-1][j-1]);
                }
            }

        }


        // reprhasing the problem
        // let x be 1 <= x <= n with k bits set
        // how many x are there?
        // note:
        //    special consideration if k = 0
        //        ans is 1;
        //    special consideration if k = 1
        //        in that case it is the pos of rightmost bit
        if( k == 0 )
            return 1;
        if( k == 5 )    // at the given constraints, max popcountDepth is 4
            return 0;

        this->n = n;
        right_most_set_bit = findRightMostSetBit(n);
        // cout << "n " << n << " right_most_set_bit " << right_most_set_bit << endl;
        if( k == 1 )
            return right_most_set_bit;


        // correct results, but will lead to TLE
        /*
        long long ans = 0LL;
        for(int i = 2; i <= right_most_set_bit+1; ++i) {
            if( _popcountDepth[i] == k ) {
                ans += rec(0LL, 0, i);
            }
        }
        */

        // to get faster               543210
        // let us assume n = 44 binary 101100, right_most_set_bit = 5 (pos 5)
        // we know that if we use bit 0 to bit 4, we cannot exceed n
        // so e.g. to see how many x we can make with 3 set bits using bit 0 to bit 4
        //    that is simply C(n,r) = C(5,3) = 10
        // now what is left to figure out is how many we can make
        //    with 3 set bits when bit 5 is set that don't exceed 44
        long long ans = 0LL;
        for(int i = 2; i <= right_most_set_bit+1; ++i) {
            if( _popcountDepth[i] == k ) {


                long long x = n;
                int r = i; // bits to set
                // we will go from right most set bit to least significant bit
                // respectively from left to right
                // once done with a position, we jump to the next pos with a set bit

                while( x && r) {
                    int pos = findRightMostSetBit(x);
                    // we are at position pos and have r bits to set
                    // w/o exceeding x
                    // it is guaranteed that bit at pos in x is set

                    // example with r = 3
                    // 101100
                    // *      we are at pos 5
                    //  ----- we can set any 3 bits
                    if( r <= pos ) {
                        // ans += nCr(pos, r); // factorial long long overflow
                                               // but if precalculated via Pascal's Triangle, we are good
                        ans += nCk[pos][r];
                    }

                    // unset bit at pos
                    x &= ~(1LL<<pos);
                    --r;

                    if( (x == 0 && r == 0) || r == 0 ) // one more valid state
                        ans += 1LL;
                }
            }
        }

        return ans;
    }
};
