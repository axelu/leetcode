
// 3687. Library Late Fee Calculator
// https://leetcode.com/problems/library-late-fee-calculator/


class Solution {
public:
    int lateFee(vector<int>& daysLate) {
        int totalLateFee = 0;
        for(int late: daysLate) {
            if( late == 1 )
                totalLateFee += 1;
            else if( late <= 5 )
                totalLateFee += 2 * late;
            else
                totalLateFee += 3 * late;
        }
        return totalLateFee;
    }
};
