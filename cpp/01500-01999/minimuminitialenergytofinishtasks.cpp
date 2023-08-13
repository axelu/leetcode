
// 1665. Minimum Initial Energy to Finish Tasks
// https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/





class Solution {
private:
    bool solve(vector<vector<int>>& tasks, int energy) {
        // cout << "solve energy " << energy << endl;
        for(auto& task: tasks) {
            if( energy < task[1] || energy < task[0] )
                return false;
            energy -= task[0];
        }
        return true;
    }

    // binary search
    int search(vector<vector<int>>& tasks, int s, int e) {
        if( e < s )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(tasks,mid);
        if( f ) {
            // can we do better?
            int t = search(tasks,s,mid-1);
            return t != -1 ? t : mid;
        }
        return search(tasks,mid+1,e);
    }

public:
    int minimumEffort(vector<vector<int>>& tasks) {
        int sum_aw = 0; // sum of actual work
        for(auto& task: tasks) {
            sum_aw += task[0];
        }
        // cout << sum_aw << endl;
        // min: sum of actual work
        // max: max(sum of actual work, max(required work))

        // it is best to do tasks first, that require the most energy to begin the task
        // it is best to do tasks first, that require the least actual energy

        sort(tasks.begin(),tasks.end(),[](const vector<int>& a, const vector<int>& b){
            // solve for this pair

            // a first
            int mna = max(a[1], b[1] + a[0]);
            // b first
            int mnb = max(b[1], a[1] + b[0]);

            return mna < mnb;
        });

        return search(tasks, sum_aw, 1000000000);
    }
};
