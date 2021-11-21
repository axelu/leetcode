
// 1319. Number of Operations to Make Network Connected
// https://leetcode.com/problems/number-of-operations-to-make-network-connected/





class Solution {
private:
    void dfs(int u, vector<int> g[], int seen[]) {
        if( seen[u] ) return;
        seen[u] = 1;

        int v;
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i];
            dfs(v,g,seen);
        }
    }
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int m = connections.size();
        // we need at least (n-1) connections
        if( m < n-1 ) return -1;

        // undirected graph with one or more connected components
        vector<int> g[n];
        for(int i = 0; i < m; ++i) {
            g[connections[i][0]].push_back(connections[i][1]);
            g[connections[i][1]].push_back(connections[i][0]);
        }

        int seen[n]; memset(seen,0,sizeof seen);
        int cc = 0; // number connected components
        for(int i = 0; i < n; ++i) {
            if( !seen[i] ) {
                dfs(i,g,seen);
                ++cc;
            }
        }
        return cc-1;
    }
};
