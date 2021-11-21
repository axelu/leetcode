
// 1523. Count Odd Numbers in an Interval Range
// https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/

class Solution {
public:
    int countOdds(int low, int high) {
        if( high - low == 0 )
            return ( high % 2 == 0 ) ? 0 : 1;

        int lr = low % 2;
        int hr = high % 2;

        int c = (high - low - 1) / 2;
        if( lr != 0 && hr != 0 ) {
            return c + 2;
        } else {
            return c + 1;
        }
    }
};
