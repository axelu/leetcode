
// 50. Pow(x, n)
// https://leetcode.com/problems/powx-n/



class Solution {
private:
    double rec(double x, double r, long f, long n) {
        // cout << "rec r " << r << " f " << f << " n " << n << endl;

        if( n == 1 ) {
            return r;
        } else if( f * 2 == n ) {
            return r*r;
        } else if( f * 2 < n ) {
            return rec(x,r*r,f*2,n);
        } else {
            return r * rec(x,x,1,n-f);
        }
    }


public:
    double myPow(double x, int n) {
        if( n == 0 )
            return 1.0;
        if( n == 1 )
            return x;
        if( n == -1 )
            return 1/x;
        if( x == 0 )    // n has to be positive if x == 0
            return x;

        long N = n;
        if( n < 0 ) {
            N *= -1;
            x = 1/x;
        }

        return rec(x,x,1,N);
    }
};
