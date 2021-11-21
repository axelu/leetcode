
// 1857. Largest Color Value in a Directed Graph
// https://leetcode.com/problems/largest-color-value-in-a-directed-graph/





class Solution {
private:
    int ans;

    void dfs(vector<int> g[], int u, int seen[], stack<int>& stck,
             string& colors, int dp[]) {

        seen[u] = 1;
        int c = colors[u]-'a';

        int v;
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i];
            if( !seen[v] )
                dfs(g,v,seen,stck,colors,dp);

            for(int j = 0; j < 26; ++j) {
                dp[u*26+j] = max(dp[u*26+j],dp[v*26+j]);
                ans = max(ans,dp[u*26+j]);
            }

        }

        ++dp[u*26+c]; // add our own color to the count
        ans = max(ans,dp[u*26+c]);

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

public:
    int largestPathValue(string& colors, vector<vector<int>>& edges) {
        int n = colors.size();

        int u,v;

        int dp[n*26];memset(dp,0,sizeof dp);

        // edges -> adjacency list
        vector<int> g[n]; // directd graph
        for(int i = 0; i < edges.size(); ++i) {
            u = edges[i][0];
            v = edges[i][1];
            if( u == v ) return -1; // defintely a cycle
            g[u].push_back(v);
        }

        ans = 0;

        // DFS
        stack<int> stck;    // visited vertices in topologial sort
        int seen[n];memset(seen,0,sizeof seen);
        for(int i = 0; i < n; ++i)
            if( !seen[i] )
                dfs(g,i,seen,stck,colors,dp);


        // vector<int> r; // node list in topological order
        unordered_map<int,int> pos;
        int idx = 0;
        while(!stck.empty()) {
            pos[stck.top()] = idx;
            // r.push_back(stck.top());
            ++idx;
            stck.pop();
        }

        for(int i = 0; i < n; ++i)
            for(int j : g[i]) {
                // parent (i) idx must be lower than child (j) idx else cyclic
                if( pos[i] > pos[j] )
                    return -1;
            }


        return ans;
    }
};
