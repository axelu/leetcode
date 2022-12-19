
// 2303. Calculate Amount Paid in Taxes
// https://leetcode.com/problems/calculate-amount-paid-in-taxes/




class Solution {
public:
    double calculateTax(vector<vector<int>>& brackets, int income) {
        int n = brackets.size();

        double ans = 0;

        int prev_upper = 0;
        for(int i = 0; i < n; ++i) {
            int curr_upper = min(brackets[i][0],income);
            ans += (curr_upper - prev_upper) * brackets[i][1] / 100.0;
            if( brackets[i][0] > income )
                break;
            prev_upper = brackets[i][0];
        }

        return ans;
    }
};
