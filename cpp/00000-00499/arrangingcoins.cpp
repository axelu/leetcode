
// 441. Arranging Coins
// https://leetcode.com/problems/arranging-coins/


class Solution {
public:
    int arrangeCoins(int n) {
        if( n <= 0 ) return 0;
        if( n == 1 ) return 1;

        long sum = 1L;
        long i = 2L;
        while( true ) {
            sum += i;
            if( sum >= (long)n ) break;
            ++i;
        }
        return sum == (long)n ? i : i-1;
    }
};
