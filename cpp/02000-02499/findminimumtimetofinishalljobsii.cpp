
// 2323. Find Minimum Time to Finish All Jobs II
// https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs-ii/




class Solution {
public:
    int minimumTime(vector<int>& jobs, vector<int>& workers) {
        // from the hint:
        //    It is always optimal to pair the worker with the least amount of time
        //    with the job that requires the least amount of time.

        sort(jobs.begin(),jobs.end());
        sort(workers.begin(),workers.end());

        int ans = 0;

        int n = jobs.size(); // jobs.length == workers.length
        for(int i = 0; i < n; ++i) {
            int d = jobs[i]/workers[i];
            if( jobs[i] % workers[i] )
                ++d;
            ans = max(ans,d);
        }

        return ans;
    }
};
