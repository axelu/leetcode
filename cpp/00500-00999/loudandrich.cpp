
// 851. Loud and Rich
// https://leetcode.com/problems/loud-and-rich/




class Solution {
private:
    void dfs(vector<int> g[], int u, int seen[], stack<int>& stck) {

        seen[u] = 1;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( !seen[v] )
                dfs(g,v,seen,stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

    pair<int,int> postorder(vector<int> g[], int u, int seen[], vector<int>& quiet, vector<pair<int,int>>& ans) {

        seen[u] = 1;

        int person = u;
        int quietness = quiet[u];

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( seen[v] ) {
                if( ans[v].second < quietness ) {
                    person = ans[v].first;
                    quietness = ans[v].second;
                }
            } else {
                auto p = postorder(g,v,seen,quiet, ans);
                if( p.second < quietness ) {
                    person = p.first;
                    quietness = p.second;
                }
            }
        }

        return ans[u] = {person,quietness};
    }

public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        // directed acyclical graph DAG
        int n = quiet.size();

        // we will create the graph in reverse
        vector<int> g[n];
        for(auto& v : richer)
            g[v[1]].push_back(v[0]);

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[n];memset(seen,0,sizeof seen);
        for(int u = 0; u < n; ++u)
            if( !seen[u] )
                dfs(g,u,seen,stck);

        // if we traverse in the topological order
        // now using dfs, when we leave a node (Postorder), we can
        // record the min quiet seen in all decsendants

        vector<pair<int,int>> t(n);
        vector<int> ans(n);
        memset(seen,0,sizeof seen);
        while( !stck.empty() ) {
            int u = stck.top();
            stck.pop();
            if( !seen[u] )
                postorder(g,u,seen,quiet,t);
            ans[u] = t[u].first;
        }

        return ans;
    }
};
