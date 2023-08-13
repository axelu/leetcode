
// 2513. Minimize the Maximum of Two Arrays
// https://leetcode.com/problems/minimize-the-maximum-of-two-arrays/





/* constraints given in problem:
 *     2 <= divisor1, divisor2 <= 10^5
 *     1 <= uniqueCnt1, uniqueCnt2 < 10^9
 *     2 <= uniqueCnt1 + uniqueCnt2 <= 10^9
 *
 * worst case: divisor1 == divisor2 == 2
 *             uniqueCnt1 + uniqueCnt2 == 10^9
 * answer: 10^9 * 2 - 1 = 1999999999
 * example: divisor1 = 2, divisor2 = 2, uniqueCnt1 = 500000000, uniqueCnt2 = 500000000
 *
 * best case: divisor1, divisor2 > uniqueCnt1+uniqueCnt2
 * answer: uniqueCnt1+uniqeCnt1
 * example: divisor1 = 21, divisor2 = 21, uniqueCnt1 = 10, uniqueCnt2 = 10
 *
 */
class Solution {
private:
    int solve_div1eqdiv2(int divisor, int n) {

        int blocks = n / (divisor-1);
        int rem    = n % (divisor-1);
        // we are loosing blocks-1 numbers along the way
        int t = (blocks * (divisor-1)) + (blocks-1);
        if( rem > 0 ) {
            t += 1 + rem; // +1 for the number after the blocks we are loosing
        }

        return t;
    }

    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }

    bool solve(long long mx, long long divisor1, long long divisor2, long long uniqueCnt1, long long uniqueCnt2) {
        // for arr1, we must have enough elements not divisible by divisor1
        long long divisible1    = mx / divisor1;   // nbr of elements between [1,mx] divisible by divisor1
        long long notdivisible1 = mx - divisible1; // nbr of elements between [1,mx] NOT divisible by divisor1
        if( uniqueCnt1 > notdivisible1 )
            return false;

        // for arr2, we must have enough elements not divisible by divisor2
        long long divisible2    = mx / divisor2;   // nbr of elements between [1,mx] divisible by divisor2
        long long notdivisible2 = mx - divisible2; // nbr of elements between [1,mx] NOT divisible by divisor2
        if( uniqueCnt2 > notdivisible2 )
            return false;

        // we need to have numbers to put in either array all together
        long long _lcm = lcm(divisor1,divisor2);
        long long divisible12    = mx / _lcm;        // nbr of elements between [1,mx] divisible by divisor1 and divisor2
        long long notdivisible12 = mx - divisible12; // nbr of elements between [1,mx] NOT divisble by divisor1 or divisor2
        if( uniqueCnt1 + uniqueCnt2 > notdivisible12 )
            return false;

        return true;
    }

public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
        if( divisor1 > uniqueCnt1+uniqueCnt2 && divisor2 > uniqueCnt1+uniqueCnt2 )
            return uniqueCnt1+uniqueCnt2;

        if( divisor1 == divisor2 )
            return solve_div1eqdiv2(divisor1,uniqueCnt1+uniqueCnt2);

        int ans = 2000000000;

        // binary search
        int s = uniqueCnt1+uniqueCnt2;
        int e = 2000000000;
        while( s <= e ) {
            int mid = s + ((e-s)/2);
            if( solve(mid,divisor1,divisor2,uniqueCnt1,uniqueCnt2) ) {
                ans = min(ans,mid);
                e = mid - 1;
            } else {
                s = mid + 1;
            }
        }

        return ans;
    }
};
