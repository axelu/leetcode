
// 3593. Minimum Increments to Equalize Leaf Paths
// https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/


class Solution {
private:
    int ans;

    long dfs( vector<vector<int>>& t, vector<int>& cost, int u, int src) {

        // at each node we capture the value for each child
        // we know how many children we have
        // as we can only increase, we pretend that we told all
        // non-max children to do so, and we report max upward

        map<long,int> mp; // value, count
        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;
            long val = dfs(t, cost, v, u);
            ++mp[val];
        }

        if( mp.empty() ) {
            // we are at a leaf
            return (long)cost[u];
        }

        int nodes_to_increase = t[u].size() - mp.rbegin()->second;
        if( u != 0 )
            --nodes_to_increase; // discount parent
        ans += nodes_to_increase;

        return (long)cost[u] + mp.rbegin()->first;
    }

public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        
        // undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1
        vector<vector<int>> t(n);
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        ans = 0;
        dfs(t, cost, 0, -1);
        return ans;
    }
};
