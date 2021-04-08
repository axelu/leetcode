
// Power of Two
// https://leetcode.com/problems/power-of-two/


class Solution {
public:
    bool isPowerOfTwo(int n) {
        if( n < 1 || n > 1073741824 ) return false; // 2^30 = 1073741824

        /* Solution 1
        if( n < 5 ) return true;

        while( n > 1 ) {
            int rem = n % 2;
            if( rem != 0 ) return false;
            n = n / 2;
        }
        return true;
        */

        return _isPowerOfTwo(n, 0, 30);
    }
private:
    bool _isPowerOfTwo(int n, int emin, int emax) {
        if ( emin == emax ) {
            return ( pow(2, emin) == n ) ? true : false;
        }

        int e = emin + (emax - emin) / 2;
        int p2 = pow(2,e);

        if( n == p2 ) {
            return true;
        } else if( n < p2 ) {
            return _isPowerOfTwo(n, emin, e);
        } else {
            return _isPowerOfTwo(n, e + 1, emax);
        }
    }
};
