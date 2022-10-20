
// 2071. Maximum Number of Tasks You Can Assign
// https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/



class Solution {
public:
    bool solve(vector<int>& tasks, vector<int>& workers, int pills, int strength, int k) {
        multiset<int> wrks; // k strongest workers
        for(int i = workers.size()-k; i < workers.size(); ++i)
            wrks.insert(workers[i]);

        // k smallest tasks
        for(int i = k-1; i >= 0; --i) { // task index
            // find the smallest worker that could execute the task
            auto lb = wrks.lower_bound(tasks[i]);
            if( lb == wrks.end() ) {
                // we need to use a pill in order to execute the task
                if( pills == 0 )
                    return false;
                // again, find the smallest worker that could excute the task
                lb = wrks.lower_bound(tasks[i]-strength);
                if( lb == wrks.end() )
                    return false;
                --pills;
            }
            wrks.erase(lb);
        }

        return true;
    }

public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        // tasks that are greater then the greatest worker + 'pill strength',
        // those tasks we will never be able to do.
        // if number workers <= number pills, we could just add strength to each worker
        // and after sorting both simply execute them in order.
        // tasks in excess of number of workers will never get done either

        // greedy = smallest worker possible takes task

        // idea:
        //   sort both tasks and workers ascending
        //   then we pick a number k and attempt for the k strongest workers
        //   to execute the k smallest tasks, we will assign workers
        //   based on our greedy definition

        sort(tasks.begin(),tasks.end());
        sort(workers.begin(),workers.end());

        // binary search
        int s = 0;
        int e = min(tasks.size(),workers.size());
        int mid;
        while(s <= e ) {
            mid = s + ((e-s)/2);
            bool f = solve(tasks,workers,pills,strength,mid);
            if( f )
                s = mid + 1;
            else
                e = mid - 1;
        }

        return e;
    }
};
