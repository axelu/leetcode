
// 2589. Minimum Time to Complete All Tasks
// https://leetcode.com/problems/minimum-time-to-complete-all-tasks/




class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        // for each time interval, collect all the tasks that could run
        // sort tasks by end time ascending
        // run tasks as late as possible to capture max overlap with later tasks
        // NOTE: a given interval can only be run once !!!

        int tsk_sz = tasks.size();

        sort(tasks.begin(),tasks.end(),[](const vector<int>& a, const vector<int>& b){
           return a[1] < b[1];
        });

        vector<vector<int>> intervals(2001,{0});                // tasks that can run in given interval
        for(int i = 0; i < tsk_sz; ++i) {                       // task
            for(int j = tasks[i][0]; j <= tasks[i][1]; ++j) {   // interval
                intervals[j].push_back(i);
            }
        }

        int ans = 0;

        for(int i = 0; i < tsk_sz; ++i) {                       // task
            int duration = tasks[i][2];
            int interval = tasks[i][1];
            while( duration > 0 ) {
                if( intervals[interval][0] == 1 ) {
                    // interval was already run
                    --interval;
                    continue;
                }

                // execute all tasks in interval
                for(int t = 1; t < intervals[interval].size(); ++t) {
                    --tasks[intervals[interval][t]][2];
                }
                // mark interval as run
                intervals[interval][0] = 1;
                // next interval
                --interval;
                --duration;
                ++ans;
            }
        }

        return ans;
    }
};
