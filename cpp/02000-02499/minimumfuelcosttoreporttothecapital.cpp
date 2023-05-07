
// 2477. Minimum Fuel Cost to Report to the Capital
// https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/




class Solution {
private:

    long long dfs(vector<int> t[], int u, int seats, int seen[], long long& ans) {

        seen[u] = 1;

        long long ret = 1LL; // the representative from our city

        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( seen[v] )
                continue;
            ret += dfs(t,v,seats,seen,ans);
        }

        // there are ret representatives traveling through our city
        // and our own representative, how many cars do we need
        // to sent to the next city?

        if( u != 0 ) {
            long long cars = ret/seats;
            if( ret % seats != 0 )
                ++cars;
            ans += cars;
        }

        return ret;
    }

public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size() + 1;

        vector<int> t[n];
        for(auto& v: roads) {
            t[v[0]].push_back(v[1]);
            t[v[1]].push_back(v[0]);
        }

        int seen[n];memset(seen,0,sizeof seen);

        long long ans = 0;

        dfs(t,0,seats,seen,ans);

        return ans;
    }
};
