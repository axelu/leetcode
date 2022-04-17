
// 1376. Time Needed to Inform All Employees
// https://leetcode.com/problems/time-needed-to-inform-all-employees/




class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {

        vector<int> G[n]; // n-ary tree rooted in headID
        for(int i = 0; i < n; ++i) {
            if( i == headID )
                continue;
            G[manager[i]].push_back(i);
        }

        int ans = 0;

        // BFS
        queue<array<int,2>> q;
        q.push({headID,0}); // communications starts at head and so far took 0 time
        int u,t,d;
        while( !q.empty() ) {
            u = q.front()[0];
            t = q.front()[1]; // time it took to get us here
            q.pop();

            if( G[u].empty() ) {
                // there are no subordinates to communicate to
                ans = max(ans,t);
                continue;
            }

            // time it took us to get here + time it takes u to inform its subordinates
            d = t + informTime[u];
            for(int k = 0; k < G[u].size(); ++k)
                q.push({G[u][k],d});
        }

        return ans;
    }
};
