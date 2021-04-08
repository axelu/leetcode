
// 1716. Calculate Money in Leetcode Bank
// https://leetcode.com/problems/calculate-money-in-leetcode-bank/


class Solution {
public:
    int totalMoney(int n) {
        int day = 0;
        int mondayAmount = 0;
        int sum = 0;
        while(true) {
            ++mondayAmount;
            // deposit Monday's amount
            sum += mondayAmount;
            ++day;
            if( day == n ) break;
            for(int i = 1; i < 7; ++i) {
                // deposit Tuesday, Wednesday, etc.
                sum += mondayAmount + i;
                ++day;
                if( day == n ) break;
            }
            if( day == n ) break;
        }

       return sum;
    }
};
