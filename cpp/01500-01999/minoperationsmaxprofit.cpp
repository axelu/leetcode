
// 1599. Maximum Profit of Operating a Centennial Wheel
// https://leetcode.com/problems/maximum-profit-of-operating-a-centennial-wheel/



class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        auto n = customers.size();
        int i = 0, q = 0, in = 0, out = 0, mp = 0, r = -1, p;
        while( i < n || q > 0 ) {
            if( i < n ) q += customers[i];

            // boarding
            if( q >= 4 ) {
                in += boardingCost * 4;
                q -= 4;
            } else {
                in += boardingCost * q;
                q = 0;
            }

            // running
            out += runningCost;

            ++i;

            // profit
            p = in - out;
            if( p > mp ) {
                mp = p;
                r = i;
            }
        }

        return r;
    }
};
