
// 3476. Maximize Profit from Task Assignment
// https://leetcode.com/problems/maximize-profit-from-task-assignment/



class Solution {
public:
    long long maxProfit(vector<int>& workers, vector<vector<int>>& tasks) {
        unordered_map<int,multiset<int,greater<int>>> tasks_by_skill; // key: skill, value: sorted list of profit

        for(auto& task: tasks) {
            int skill = task[0];
            int profit = task[1];
            tasks_by_skill[skill].insert(profit);
        }

        long long ans = 0LL;

        for(int worker: workers) {
            // we have this worker execute the task with greatest profit
            // matching her skill if it exists
            auto f = tasks_by_skill.find(worker);
            if( f != tasks_by_skill.end() ) {
                ans = ans + (long long)*(f->second.begin());
                f->second.erase(f->second.begin());
                if( f->second.empty() )
                    tasks_by_skill.erase(f);
            }
        }

        // we have one more worker joining who can execute any task
        // we will have her execute the task left with the greatest profit
        int mx = 0;
        for(auto it: tasks_by_skill)
            mx = max(mx, *it.second.begin());

        return ans + (long long)mx;
    }
};
