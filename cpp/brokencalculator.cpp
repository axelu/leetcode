
// 991. Broken Calculator
// https://leetcode.com/problems/broken-calculator/
// day 21 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3647/



class Solution {
public:
    int brokenCalc(int X, int Y) {
        if( X == Y ) return 0;
        if( X > Y ) return X - Y;

        int ans = 0;
        while( Y > X ) {
            if( Y % 2 == 1 ) {
                ++Y;
                ++ans;
            }
            Y /= 2;
            ++ans;
        }
        ans += X - Y;
        return ans;
    }
};
