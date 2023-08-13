
// 2798. Number of Employees Who Met the Target
// https://leetcode.com/problems/number-of-employees-who-met-the-target/




class Solution {
public:
    int numberOfEmployeesWhoMetTarget(vector<int>& hours, int target) {
        int n = hours.size(); // nbr of employees

        int ans = 0;
        for(int x: hours)
            if( x >= target )
                ++ans;

        return ans;
    }
};
