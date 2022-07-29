
// 1761. Minimum Degree of a Connected Trio in a Graph
// https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/



class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        int degree[n+1];memset(degree,0,sizeof degree);
        int connected[n+1][n+1];memset(connected,0,sizeof connected);

        vector<int> g[n+1]; // undirected graph
        for(auto& v : edges) {
            // v[0] -> v[1]
            g[v[0]].push_back(v[1]);
            ++degree[v[0]];
            // v[1] -> v[0]
            g[v[1]].push_back(v[0]);
            ++degree[v[1]];
            // record that v[0] and v[1] are directly connected
            connected[v[0]][v[1]] = 1;
            connected[v[1]][v[0]] = 1;
        }

        int ans = INT_MAX;

        // TODO we will run accross a connected trio multiple times
        //      constraints are small, so it maybe ok
        for(int u = 1; u <= n; ++u) {
            // obvioulsy u is connected to g[u][i]
            int adj_size = g[u].size();
            for(int i = 0; i < adj_size-1; ++i) {
                int v = g[u][i];
                for(int j = i+1; j < adj_size; ++j) {
                    int w = g[u][j];
                    if( connected[v][w] ) {
                        // we found a connected trio u, v, w
                        ans = min(ans,degree[u]+degree[v]+degree[w]-6);
                    }
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
