
// 802. Find Eventual Safe States
// https://leetcode.com/problems/find-eventual-safe-states/




class Solution {
private:
    int dfs(vector<vector<int>>& graph, int u, int seen[], int safe[]) {
        // dfs on graph starting at u
        // returns 0 if u is unsafe, 1 if u is safe

        // have we seen u already during a different exploration?
        if( safe[u] != -1 )
            return safe[u];

        // if we have seen u already in our current path,
        // then we have a cycle and with that,
        // any node in the path that got us here is unsafe
        if( seen[u] )
            return 0;

        seen[u] = 1;

        int ret = 1;
        for(int i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i];
            int t = dfs(graph,v,seen,safe);
            if( t == 0 )
                ret = 0;
        }

        return safe[u] = ret;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        // directed graph of n nodes with each node labeled from 0 to n - 1
        int n = graph.size();

        // -1 unseen, 0 unsafe, 1 safe
        int safe[n];memset(safe,-1,sizeof safe);

        vector<int> ans;

        int seen[n];
        for(int u = 0; u < n; ++u)
            if( safe[u] == -1 ) {
                memset(seen,0,sizeof seen);
                if( dfs(graph,u,seen,safe) )
                    ans.push_back(u);
            } else if( safe[u] == 1 ) {
                ans.push_back(u);
            }

        return ans;
    }
};
