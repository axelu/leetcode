
// 2457. Minimum Addition to Make Integer Beautiful
// https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/




/*
 *  1 <= n <= 1e12
 *  2109876543210
 *  1000000000000
 *   999999999999  -> max digit sum 12*9 = 108
 *
 *  example n = 316, target = 3
 *      initial digit sum = 10
 *      in order to make a difference we need to add till we cross the next period
 *      316 -> 316 +   4 =  320, we reduced digit sum by 6 but added 1: 10 - 6 + 1 = 5
 *      320 -> 320 +  80 =  400, we reduced digit sum by 2 but added 1:  5 - 2 + 1 = 4
 *      400 -> 400 + 600 = 1000, we reduced digit sum by 4 but added 1:  4 - 4 + 1 = 1, we are done 1 < 3
 *
 *      we need to watch out if the digit to the left is a 9!!!
 * example n = 396, target = 3
 *      initial digit sum = 18
 *      396 -> 396 +   4 =  400, digit sum 4
 *      400 -> 400 + 600 = 1000, digit sum 1, we are done 1 < 3
 */
class Solution {
private:
    int digitsum(long long x) {
        int digit_sum = 0;
        while( x > 0 ) {
            digit_sum += x % 10;
            x /= 10;
        }
        return digit_sum;
    }

public:
    long long makeIntegerBeautiful(long long n, int target) {
        int digit_sum = digitsum(n);
        if( digit_sum <= target )
            return 0;

        long long ans = 0;
        long long f = 1;
        while( digit_sum > target ) {

            int rem = n % 10;
            int t = 10 - rem;

            n = (n + t) / 10;

            digit_sum = digitsum(n);

            ans = ans + f * t;
            f*= 10;
        }

        return ans;
    }
};
