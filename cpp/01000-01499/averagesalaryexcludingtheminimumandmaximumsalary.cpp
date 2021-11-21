
// 1491. Average Salary Excluding the Minimum and Maximum Salary
// https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/


class Solution {
public:
    double average(vector<int>& salary) {
        int s_min = INT_MAX;
        int s_max = INT_MIN;

        double s = 0.0;
        for(int i : salary) {
            s_max = max(s_max,i);
            s_min = min(s_min,i);
            s += i;
        }

        return (s - s_max - s_min) / (salary.size() - 2);
    }
};
