
// 2927. Distribute Candies Among Children III
// https://leetcode.com/problems/distribute-candies-among-children-iii/




/* example n = 10, limit = 6 -> answer = 36
 * when we distribute x items to two children we have the following formulas:
 *   case A: x <= limit                               x + 1
 *   case B: x >  limit && x <= 2 * limit && x odd:   ((limit - (x / 2)) * 2)
 *   case C: x >  limit && x <= 2 * limit && x even:  ((limit - (x / 2)) * 2) + 1
 *   case D: x >  2 * limit:                           0
 *
 *   child 0  child 1+2
 *                x
 *      6         4      case A  4 + 1                    5
 *      5         5      case A  5 + 1                    6
 *      4         6      case A  6 + 1                    7
 *      3         7      case B  ((6 - (7/2)) * 2)        6
 *      2         8      case C  ((6 - (8/2)) * 2) + 1    5
 *      1         9      case B  ((6 - (9/2)) * 2)        4
 *      0        10      case C  ((6 - (10/2)) * 2) + 1   3
 *                                                      ----
 *                                                       36
 */
class Solution {
public:
    long long distributeCandies(int n, int limit) {
        if( limit * 3 < n )
            return 0;
        if( limit * 3 == n )
            return 1;

        if( limit >= n ) {
            // the question becomes:
            //      in how many ways can we distribute n identical objects to r distinct boxes,
            //      so that each box is filled with 0 or more onjects?
            //      the number of ways we can distribute = n+r-1Cr-1
            //
            // n+r-1Cr-1 -> r = 3 in our case -> n+2C2
            // nCr = fact(n) / (fact(r) * fact(n - r))
            // simplifies to:
            long long t = ((long long)n + 1LL) * ((long long)n + 2LL) / 2LL;
            return t;
        }

        /*
        long long ans = 0LL;

        // brute force
        // for the 1st position
        //      lower limit s is max(0, n - 2 * limit)
        //      upper limit e is limit

        int s = max(0, n - 2*limit);        // cout << "s " << s << endl;
        int e = limit;                      // cout << "e " << e << endl;
        for(int i = e; i >= s; --i) {       // number of candies at 1st position
            long long x = n - i;            // number of candies at postion 2+3
            if( x <= limit ) {              // case A
                ans += x + 1LL;
            } else if( x % 2LL ) {          // case B
                ans += (((long long)limit - (x / 2LL)) * 2LL);
            } else {                        // case C
                ans += (((long long)limit - (x / 2LL)) * 2LL) + 1LL;
            }
        }

        return ans;
        */

        // for the 1st position
        //      lower limit s is max(0, n - 2 * limit)
        //      upper limit e is limit
        // hence for positions 2+3 we have range
        //      low    n - limit
        //      high   n - max(0, n - 2 * limit)
        long long s2 = n - limit;                 // cout << "s2 " << s2 << endl;
        long long e2 = n - max(0, n - 2 * limit); // cout << "e2 " << e2 << endl;

        // case A:
        //     so when do we cross limit? obviosly at limit.
        //     (sum of integers 1 to limit+1) - (sum of integers 1 to (n-limit));
        //      remember: n(n+1)/2 is formula for the sum of integers 1 to n
        long long a = 0LL;
        if( s2 <= limit) {
            long long a1 = ((long long)limit + 1LL) * ((long long)limit + 2LL) / 2LL;
            long long a2 = s2 * (s2 + 1LL) / 2LL;
            a  = a1 - a2;
        }
        // cout << "a " << a << endl;

        // CASE B and C:
        //     our range is max(limit + 1, s2) to e2 inclusive
        long long sbc = max((long long)limit + 1LL, s2);
        long long f = e2 - (sbc - 1LL);
        //     how many even and how many odd numbers in that range?
        long long even = sbc % 2LL && e2 % 2LL ? (e2 - sbc) / 2LL : ((e2 - sbc) / 2LL) + 1LL;
        long long odd  = f - even;
        // cout << "f " << f << " even " << even << " odd " << odd << endl;

        long long t1 = e2 * (e2 + 1LL) / 2LL;
        long long t2 = (sbc-1LL) * sbc / 2LL;

        // because in the brute force method, uneven numbers / 2 basically get floored,
        // as that is not happening here, we need to compensate by
        // adding the range instead of just number of evens
        // long long bc = ((f * limit) - ((t1 - t2) / 2LL)) * 2LL + even;
        long long bc = ((f * limit) - ((t1 - t2) / 2LL)) * 2LL + f;
        // if number of odd numbers in range is odd, subtract 1
        if( odd % 2 )
            --bc;

        return a + bc;
    }
};
