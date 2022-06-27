
// 2192. All Ancestors of a Node in a Directed Acyclic Graph
// https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/




// see also 851. Loud and Rich https://leetcode.com/problems/loud-and-rich/

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

    void postorder(vector<int> g[], int u, int seen[], vector<vector<int>>& ans) {

        seen[u] = 1;

        vector<int> ancestors;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];

            // v is an ancestor of u
            ancestors.push_back(v);

            if( !seen[v] )
                postorder(g,v,seen,ans);

            ancestors.insert(ancestors.end(),ans[v].begin(),ans[v].end());
        }

        if( ancestors.size() > 1 ) {
            sort(ancestors.begin(),ancestors.end());
            for(auto it = next(ancestors.begin()); it != ancestors.end(); )
                if( *prev(it) == *it )
                    it = ancestors.erase(it);
                else
                    ++it;
        }
        ans[u] = ancestors;
        return;
    }

public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        // directed acyclic graph DAG

        // we will create the graph in reverse
        vector<int> g[n];
        for(auto& edge : edges)
            g[edge[1]].push_back(edge[0]);

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[n];memset(seen,0,sizeof seen);
        for(int u = 0; u < n; ++u)
            if( !seen[u] )
                dfs(g,u,seen,stck);

        // if we traverse in the topological order
        // now using dfs, when we leave a node (Postorder), we can
        // record the all ancestors

        vector<vector<int>> ans(n);
        memset(seen,0,sizeof seen);
        while( !stck.empty() ) {
            int u = stck.top();
            stck.pop();
            if( !seen[u] )
                postorder(g,u,seen,ans);
        }

        return ans;
    }
};
