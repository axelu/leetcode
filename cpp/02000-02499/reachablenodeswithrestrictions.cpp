
// 2368. Reachable Nodes With Restrictions
// https://leetcode.com/problems/reachable-nodes-with-restrictions/





class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        // undirected tree rooted in 0

        vector<bool> _restricted(n,false);
        for(int u: restricted)
            _restricted[u] = true;

        vector<int> g[n];
        for(auto& v: edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        int ans = 0;

        // BFS
        queue<int> q;
        q.push(0);
        vector<bool> seen(n,false);
        seen[0] = true;
        while( !q.empty() ) {
            int u = q.front();
            q.pop();

            ++ans;

            for(int i = 0; i < g[u].size(); ++i) {
                int v = g[u][i];

                if( !_restricted[v] && !seen[v] ) {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }

        return ans;
    }
};
