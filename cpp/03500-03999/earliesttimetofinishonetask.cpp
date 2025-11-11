
// 3683. Earliest Time to Finish One Task
// https://leetcode.com/problems/earliest-time-to-finish-one-task/




class Solution {
public:
    int earliestTime(vector<vector<int>>& tasks) {
        int ans = INT_MAX;
        for(auto& task: tasks)
            ans = min(ans, task[0] + task[1]);

        return ans;
    }
};
