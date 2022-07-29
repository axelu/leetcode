
// 2204. Distance to a Cycle in Undirected Graph
// https://leetcode.com/problems/distance-to-a-cycle-in-undirected-graph/



class Solution {
private:
    unordered_set<int> cycle;

    int dfs(vector<int> g[], int u, int seen[], int src, int path[]) {

        seen[u] = 1;
        path[u] = 1;

        int ret = -1;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( v == src )
                continue;
            if( path[v] ) {
                // we found our cycle
                // node u is part of the cycle
                cycle.insert(u);
                ret = v;
                break;
            }
            if( !seen[v] ) {
                int t = dfs(g,v,seen,u,path);
                if( t != -1 ) {
                    // node u is part of the cycle
                    cycle.insert(u);
                    if( t != u )
                        ret = t;
                    break;
                }
            }
        }

        path[u] = 0;
        return ret;
    }

    void dfs2(vector<int> g[], int u, int src, int step, vector<int>& ans) {

        ans[u] = step;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( v == src || cycle.count(v) )
                continue;
            dfs2(g,v,u,step+1,ans);
        }
    }

public:
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        // first lets determine all nodes that are in the cycle
        // then we do a DFS from those nodes

        vector<int> g[n]; // undirected graph
        for(auto& edge : edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        int seen[n];memset(seen,0,sizeof seen);
        int path[n];memset(path,0,sizeof path);
        for(int u = 0; u < n; ++u)
            if( !seen[u] && cycle.empty() )
                dfs(g,u,seen,-1,path);

        // start a dfs from all nodes in cycle
        vector<int> ans(n);
        for(auto it = cycle.begin(); it != cycle.end(); ++it)
            dfs2(g,*it,-1,0,ans);

        return ans;
    }
};
