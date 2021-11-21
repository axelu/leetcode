
// 2008. Maximum Earnings From Taxi
// https://leetcode.com/problems/maximum-earnings-from-taxi/




class Solution {
private:

    long long rec(vector<array<int,2>> g[] ,int n, int u, long long mem[]) {
        if( u == n )
            return 0LL;

        if( mem[u] != -1 )
            return mem[u];

        // we have a choice
        // pick up a ride at our current point (if any)
        // and continue where that ride ends OR
        // skip the current point and pick up a ride at the next point

        // take
        long long ret = 0LL;
        long long t;
        for(int i = 0; i < g[u].size(); ++i) {
            t = (long long)g[u][i][0]-(long long)u+(long long)g[u][i][1]+rec(g,n,g[u][i][0],mem);
            ret = max(ret,t);
        }

        // skip
        t = rec(g,n,u+1,mem);
        ret = max(ret,t);

        return mem[u] = ret;
    }


public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {

        vector<array<int,2>> g[n]; // points on a road 1-indexed; endpoint,tip

        int n_rides = rides.size();
        for(int i = 0; i < n_rides; ++i)
            g[rides[i][0]].push_back({rides[i][1],rides[i][2]});

        long long mem[n];memset(mem,-1,sizeof mem); // max profit starting from i

        return rec(g,n,1,mem);
    }
};
