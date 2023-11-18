
// 2895. Minimum Processing Time
// https://leetcode.com/problems/minimum-processing-time/





class Solution {
public:
    int minProcessingTime(vector<int>& processorTime, vector<int>& tasks) {
        int tasks_sz = tasks.size();
        // 1 <= n == processorTime.length <= 25000
        // tasks.length == 4 * n

        // greedily assign longest taking tasks to processors that come online first
        sort(begin(processorTime),end(processorTime));
        sort(begin(tasks),end(tasks),greater<int>());

        int ans = 0;
        int proc_idx = 0;
        for(int task_idx = 0; task_idx < tasks_sz; ++task_idx) { // task index
            ans = max(ans, processorTime[proc_idx] + tasks[task_idx]);
            if( (task_idx+1) % 4 == 0 ) {
                ++proc_idx;
            }
        }

        return ans;
    }
};
