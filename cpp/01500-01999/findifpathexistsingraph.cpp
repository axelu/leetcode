
// 1971. Find if Path Exists in Graph
// https://leetcode.com/problems/find-if-path-exists-in-graph/




class Solution {
private:
    bool dfs(vector<int> g[], int u, int seen[], int end) {
        if( u == end )
            return true;

        seen[u] = 1;

        int v;
        for(int i = 0; i < g[u].size(); ++i) {
           v = g[u][i];
           if( !seen[v] && dfs(g,v,seen,end) )
               return true;
        }
        return false;
    }

public:
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {

        vector<int> g[n]; // undirected graph
        for(int i = 0; i < edges.size(); ++i) {
            g[edges[i][0]].push_back(edges[i][1]);
            g[edges[i][1]].push_back(edges[i][0]);
        }

        int seen[n];memset(seen,0,sizeof seen);
        return dfs(g,start,seen,end);
    }
};
