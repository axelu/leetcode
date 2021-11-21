
// 242. Integer Break
// https://leetcode.com/problems/integer-break/





//  2 ->   1        1 1
//  3 ->   2        1 2
//  4 ->   4        2 2
//  5 ->   6        2 3
//  ...
//  7 ->  12      2 2 3
//  8 ->  18      2 3 3
//  9 ->  27      3 3 3
// 10 ->  36      3 3 4
// 11 ->  54    2 3 3 3
// 12 ->  81    3 3 3 3
// 13 -> 108    3 3 3 4
// 14 -> 162  2 3 3 3 3
// ...


class Solution {
public:
    int integerBreak(int n) {
        // 2 <= n <= 58
        if( n == 2 )
            return 1;
        if( n == 3 )
            return 2;
        if( n == 4 )
            return 4;

        int sum = 0;
        int i = 0;
        while( true ) {
            sum += 3;
            ++i;
            if( n - sum <= 4 )
                break;
        }

        return pow(3,i)*(n-sum);
    }
};
