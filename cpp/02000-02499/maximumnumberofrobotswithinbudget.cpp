
// 2398. Maximum Number of Robots Within Budget
// https://leetcode.com/problems/maximum-number-of-robots-within-budget/



class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        int n = chargeTimes.size(); // chargeTimes.length == runningCosts.length
        
        int ans = 0;
        
        map<long long,int> mp;  // chargetime, count
        long long sum = 0;      // sum of running costs in current sliding window
        long long mct;          // max of charge times in current sliding window
        int k;                  // lenght of current sliding window
        for(int i = 0, j = 0; j < n; ++j) {
            ++mp[chargeTimes[j]];
            mct = prev(mp.end())->first;

            sum += runningCosts[j];
            
            k = j - i + 1;
            
            long long cost = mct + k * sum;
            
            while( cost > budget ) {
                --mp[chargeTimes[i]];
                if( mp[chargeTimes[i]] == 0 )
                    mp.erase(chargeTimes[i]);
                if( !mp.empty() )
                    mct = prev(mp.end())->first;
                else
                    mct = 0;
                
                sum -= runningCosts[i];
                
                --k;
                ++i;
                cost = mct + k * sum;
            }
            
            ans = max(ans,k);
        }
        
        return ans;
    }
};
