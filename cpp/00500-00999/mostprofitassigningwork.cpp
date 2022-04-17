
// 826. Most Profit Assigning Work
// https://leetcode.com/problems/most-profit-assigning-work/



class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        // order jobs by highest profit and lowest difficulty
        // assign tasks after sorting to the lowest skill worker possible
        // execute as many jobs with the highest profit as possible

        int n = difficulty.size(); // difficulty.length == profit.length
        vector<array<int,2>> jobs(n);
        for(int i = 0; i < n; ++i)
            jobs[i] = {profit[i],difficulty[i]};

        sort(jobs.begin(),jobs.end(),[](const array<int,2>& a, const array<int,2>& b) {
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        int m = worker.size();
        map<int,int> workforce; // difficulty,number of workers
        for(int i = 0; i < m; ++i) {
            auto p = workforce.insert({worker[i],1});
            if( !p.second )
                ++p.first->second;
        }

        int ans = 0;
        for(int i = 0; i < n; ++i) {
            // assign the current job to the lowest skilled available worker
            // as often as we can
            auto f = workforce.lower_bound(jobs[i][1]);
            while( f != workforce.end() ) {
                ans += jobs[i][0];
                --f->second;
                if( f->second == 0 )
                    workforce.erase(f);
                f = workforce.lower_bound(jobs[i][1]);
            }
        }

        return ans;
    }
};
