
// 2543. Check if Point Is Reachable
// https://leetcode.com/problems/check-if-point-is-reachable/





/* gcd(a,b) does not change if we subtract the larger from the smaller, or add
 * a < b: gcd(a,b) == gcd(a,b-a)
 * a > b: gcd(a,b) == gcd(a,a-b)
 * gcd(a,b) == gcd(a+b,b) == gcd(a,a+b)
 *
 * test cases
 * 6,9
 * 4,7
 * 3,7
 * 536870912,536870912
 * 1000000000,999999999
 * 339513622,655934895
 */
class Solution {
private:
    // greatest common denominator
    int gcd(int a, int b) {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }

    unordered_set<long> seen;

    bool rec(long x, long y) {
        // cout << "rec x " << x << " y " << y << endl;

        if( x == 1 || y == 1 )
            return true;

        int _gcd = gcd(x,y);
        // cout << "_gcd " << _gcd << endl;
        if( _gcd == 1 )
            return true;
        if( _gcd % 2 == 1 )
            return false;

        long key = (x<<31) + y;
        seen.insert(key);

        if( x % 2 == 1 && y % 2 == 1 ) { // both are odd
            long tmp_key = ((x+y)<<31) + y;
            if( seen.find(tmp_key) == seen.end() ) {
                bool f = rec(x+y,y);
                if( f )
                    return true;
            }
            tmp_key = (x<<31) + (y+x);
            if( seen.find(tmp_key) == seen.end()  )
                return rec(x,y+x);
        }

        long t1 = x;
        if( x % 2 == 0 ) {
            while( t1 % 2 == 0 ) {
                t1 /= 2;
            }
            long tmp_key = (t1<<31) + y;
            if( seen.find(tmp_key) == seen.end()  ) {
                bool f = rec(t1,y);
                if( f )
                    return true;
            }
        }

        long t2 = y;
        if( y % 2 == 0 ) {
            while( t2 % 2 == 0 ) {
                t2 /= 2;
            }
            long tmp_key = (x<<31) + t2;
            if( seen.find(tmp_key) == seen.end() ) {
                bool f = rec(x,t2);
                if( f )
                    return true;
            }
        }

        return false;
    }

public:
    bool isReachable(int targetX, int targetY) {
        if( targetX == 1 && targetY == 1 )
            return true;

        // startX = 1, startY = 1
        // forward operations
        //     (  x, y-x)
        //     (x-y,   y)
        //     (2*x,   y)
        //     (  x, 2*y)
        // with that, if we would start at targetX and targetY
        // backward operations
        //     (x+y,   y)
        //     (  x, y+x)
        //     (x/2,   y) if x is even
        //     (  x, y/2) if y is even

        // if we can reduce one, targetX or targetY to 1, we have a solution
        // example: 8 -> 8/2 = 4 -> 4/2 = 2 -> 2/2 = 1
        // but:     6 -> 6/2 = 3, we would need to add an odd number, to get back to an even

        if( targetX % 2 == 0 ) {
            int t = targetX;
            while( true ) {
                t /= 2;
                if( t % 2 )
                    break;
            }
            if( t == 1 )
                return true;
        }

        if( targetY % 2 == 0 ) {
            int t = targetY;
            while( true ) {
                t /= 2;
                if( t % 2 )
                    break;
            }
            if( t == 1 )
                return true;
        }

        return rec(targetX,targetY);
    }
};
