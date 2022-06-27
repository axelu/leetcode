
// 1462. Course Schedule IV
// https://leetcode.com/problems/course-schedule-iv/




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

    void postorder(vector<int> g[], int u, int seen[], vector<unordered_set<int>>& ans) {

        seen[u] = 1;

        unordered_set<int> ancestors;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];

            // v is an ancestor of u
            ancestors.insert(v);

            if( !seen[v] )
                postorder(g,v,seen,ans);

            for(int x : ans[v])
                ancestors.insert(x);
        }

        ans[u] = ancestors;
        return;
    }

public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {

        // directed acyclic graph DAG

        // we will create the graph in reverse
        vector<int> g[numCourses];
        for(auto& edge : prerequisites)
            g[edge[1]].push_back(edge[0]);

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[numCourses];memset(seen,0,sizeof seen);
        for(int u = 0; u < numCourses; ++u)
            if( !seen[u] )
                dfs(g,u,seen,stck);

        // if we traverse in the topological order
        // now using dfs, when we leave a node (Postorder), we can
        // record the all ancestors

        vector<unordered_set<int>> t(numCourses);
        memset(seen,0,sizeof seen);
        while( !stck.empty() ) {
            int u = stck.top();
            stck.pop();
            if( !seen[u] )
                postorder(g,u,seen,t);
        }

        // answer each query
        int q_sz = queries.size();
        vector<bool> ans(q_sz,false);
        for(int i = 0; i < q_sz; ++i)
            if( t[queries[i][1]].count(queries[i][0]) )
                ans[i] = true;

        return ans;
    }
};
