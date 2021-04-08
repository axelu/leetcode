

// 323. Number of Connected Components in an Undirected Graph
// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/






class Solution {
private:
    void dfs(int v, vector<int> t[], int seen[]) {
        if( seen[v] ) return;
        seen[v] = 1;
        for(int i = 0; i < t[v].size(); ++i)
            dfs(t[v][i],t,seen);
    }

public:
    int countComponents(int n, vector<vector<int>>& edges) {
        if( n == 0 ) return 0;
        if( n == 1 ) return 1;
        
        vector<int> t[n];
        for(int i = 0; i < edges.size(); ++i) {
            t[edges[i][0]].push_back(edges[i][1]);
            t[edges[i][1]].push_back(edges[i][0]);
        }
        int seen[n]; memset(seen,0,sizeof seen);

        int ans = 0;
        for(int i = 0; i < n; ++i)
            if( !seen[i] ) {
                dfs(i,t,seen);
                ++ans;
            }
        return ans;
    }
};

