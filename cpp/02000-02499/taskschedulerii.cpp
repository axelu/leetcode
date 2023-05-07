
// 2365. Task Scheduler II
// https://leetcode.com/problems/task-scheduler-ii/



class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        int n = tasks.size();

        unordered_map<int,long long> earliest; // task, earliest possible execution

        long long day = 0LL;

        for(int i = 0; i < n; ++i) {
            ++day;

            // can we execute the current task?
            auto f = earliest.find(tasks[i]);
            if( f == earliest.end() || f->second <= day ) {
                earliest[tasks[i]] = day + space + 1;
            } else {
                // we have to take a break till the day we can execute the current task
                day = f->second; // advance the day to the day at which we can execute the current task
                f->second = day + space + 1;
            }
        }

        return day;
    }
};
