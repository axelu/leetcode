
// 829. Consecutive Numbers Sum
// https://leetcode.com/problems/consecutive-numbers-sum/




/* example 472330709
 *     i 12429736 j 12429774
 *     i 24859501 j 24859520
 *     i 236165353 j 236165355
 *     -> ans = 4 (includes 472330709 itself)
 *
 * sum of 1st n positive integers
 * sum = n(n + 1)/2
 * -> n^2 + n − (2*sum) = 0
 * apply Sridharacharya formula
 * https://www.vedantu.com/question-answer/the-formula-of-the-sum-of-first-n-natural-class-11-maths-cbse-5ee862757190f464f77a1c68
 * n = (-1 + sqrt(1 + 4*(2*sum)))/2
 * so with above formula we could calculate where to start/end our search
 *
 * x + (x+1) + (x+2) + ... + (x+(k-1)) = n
 * resolves to k*x + k*(k-1)/2         = n
 * resolves to k*x                     = n - k*(k-1)/2
 * so if the right hand side is a multiple k, then we have a solution
 */
class Solution {
public:
    int consecutiveNumbersSum(int n) {
        if( n == 1 )
            return 1;

        // 1 <= n <= 10^9
        // sum[1,44721] = 1000006281

        int ans = 1; // n itself is considered an ans

        int k = 2;
        int kx = n - k*(k-1)/2;
        while( kx > 0 ) {
            if( kx % k == 0 )
                ++ans;
            ++k;
            kx = n - k*(k-1)/2;
        }



        // pass 2 TLE
        /*
        // if n is odd, then we stop at n/2 + 1
        // if n is even, then we stop at n/2 - 1
        // discover 1st window, if any
        int j = n % 2 == 1 ? n/2 + 1 : n/2;
        int i = j - 1;
        int sum = i + j;
        int j_min = (-1 + sqrt(1 + 4*(2*(long)n)))/2;
        // cout << "j_min " << j_min << endl;

        while( i > 1 ) {
            // cout << "sum " << sum << " i " << i << " j " << j << endl;
            while( sum > n && j > j_min) {
                sum -= j;
                --j;
                --i;
                sum += i;
            }
            if( j < j_min + 1 )
                break;
            while( i > 1 && sum < n ) {
                --i;
                sum += i;
            }
            if( sum == n ) {
                ++ans;
                sum -= j;
                --j;
                --i;
                sum += i;
                --i;
                sum += i;
            }
        }
        // cout << "sum " << sum << " i " << i << " j " << j << endl;
        */

        // pass 1 TLE
        /*
        int limit = n % 2 == 1 ? n/2 + 1 : n/2;
        int sum = 0;
        int i = 0;
        int j = 0;
        while( j + 1 <= limit ) {
            ++j;
            sum += j;

            while( i < j && sum > n ) {
                ++i;
                sum -= i;
            }
            if( sum == n ) {
                cout << " i " << i << " j " << j << endl;
                ++ans;
            }
        }

        cout << "sum " << sum << " i " << i << " j " << j << endl;
        */

        return ans;
    }
};
