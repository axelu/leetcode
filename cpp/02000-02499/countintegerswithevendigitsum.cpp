
// 2180. Count Integers With Even Digit Sum
// https://leetcode.com/problems/count-integers-with-even-digit-sum/


class Solution {
public:
    int countEven(int num) {
        int ans = 0;
        int x,t;
        for(int i = 1; i <= num; ++i) {
            t = 0;
            x = i;
            while(x > 0) {
                t += x % 10;
                x /= 10;
            }
            if( t % 2 == 0 )
                ++ans;
        }

        return ans;
    }
};
