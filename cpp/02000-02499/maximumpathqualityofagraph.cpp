
// 2065. Maximum Path Quality of a Graph
// https://leetcode.com/problems/maximum-path-quality-of-a-graph/




class Solution {
private:
    int ans;

    void dfs(vector<array<int,2>> g[], vector<int>& values, int u, int t, int maxTime, int s,
             int seen[]) {

        // t == time it took us to get here
        // s == amount collected

        if( t > maxTime )
            return;

        // from the constraints: There are at most four edges connected to each node.
        // hence it doesn't make sense to see a node more than 5 times
        if( seen[u] > 5 )
            return;

        // if we are seeing u for the 1st time, then we can collect
        if( seen[u] == 0 )
            s += values[u];

        // if we are at node 0 record current amount collected
        if( u == 0 )
            ans = max(ans,s);

        // record our visit to u
        ++seen[u];

        int v,weight; // weight is cost
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i][0];
            weight = g[u][i][1];
            dfs(g,values,v,t+weight,maxTime,s,seen);
        }

        // backtrack
        --seen[u];
    }
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();

        // undirected weighted graph
        vector<array<int,2>> g[n];
        for(auto &v : edges ) {
            g[v[0]].push_back({v[1],v[2]});
            g[v[1]].push_back({v[0],v[2]});
        }

        int seen[n];memset(seen,0,sizeof seen);
        ans = 0;
        dfs(g,values,0,0,maxTime,0,seen);
        return ans;
    }
};
