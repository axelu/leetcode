
// 29. Divide Two Integers
// https://leetcode.com/problems/divide-two-integers/
// day 27 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3654/


// https://www.geeksforgeeks.org/divide-two-integers-without-using-multiplication-division-mod-operator/
class Solution {
private:
    int divideByBitManipulation(long long dividend, long long divisor) {
        long long quotient = 0;
        long long temp = 0;

        // test down from the highest bit and
        // accumulate the tentative value for
        // valid bit
        for(int i = 31; i >= 0; --i) {
            if( temp + (divisor << i) <= dividend ) {
                temp += divisor << i;
                quotient |= 1LL << i;
            }
        }

        return quotient;
    }

public:
    int divide(int dividend, int divisor) {
        // -2^31 <= dividend, divisor <= 2^31 - 1
        // divisor != 0
        // without using multiplication, division or mod operator

        // base cases
        if( dividend ==  0 ) return 0;
        if( divisor  ==  1 ) return dividend;
        if( divisor  == -1 ) {
            // from the problem:
            // Assume we are dealing with an environment that could
            // only store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1].
            // For this problem, assume that your function returns 2^31 − 1
            // when the division result overflows.
            if( dividend == INT_MIN ) return INT_MAX;
            return -dividend;
        }
        if( dividend > INT_MIN ) {
            if( abs(dividend) == abs(divisor) )
                return (( dividend < 0 && divisor > 0 ) || ( dividend > 0 && divisor < 0 )) ? -1 : 1;
            if( dividend > INT_MIN && abs(dividend) < abs(divisor) ) return 0;
        }

        int ans = divideByBitManipulation(abs(dividend),abs(divisor));
        return (( dividend < 0 && divisor > 0 ) || ( dividend > 0 && divisor < 0 )) ? -ans : ans;
    }
};
