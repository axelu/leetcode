
// 3067. Count Pairs of Connectable Servers in a Weighted Tree Network
// https://leetcode.com/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network





class Solution {
private:

    int dfs(vector<pair<int,int>> t[], int u, int src, int dist, int signalSpeed) {
        int ret = 0;

        if( dist % signalSpeed == 0 )
            ++ret;

        int m = t[u].size();
        for(int i = 0; i < m; ++i) {
            int v = t[u][i].first;
            if( v == src )
                continue;
            int weight = t[u][i].second;
            ret += dfs(t, v, u, dist + weight, signalSpeed);
        }

        return ret;
    }

public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        // edges.length == n - 1
        // edges[i] = [ai, bi, weighti]

        int n = edges.size() + 1;

        vector<pair<int,int>> t[n]; // v, weight
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            t[u].push_back({v,weight});
            t[v].push_back({u,weight});
        }

        // run a DFS with for every node as the root
        // for each direct child of root, we record the number of nodes
        // in the given child tree whose distance is divisible by signalSpeed
        // we can combine each child in a given subtree tree with every child in any other subtree
        // we must not combine the children in the same subtree though!
        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            int a = 0;
            int rs = 0; // running total of nodes in i's subtree whose distance to i is divisible by signalSpeed
            int m = t[i].size();
            for(int j = 0; j < m; ++j) {
                int c = t[i][j].first;
                int weight = t[i][j].second;
                int count = dfs(t, c, i, weight, signalSpeed);
                // we can make pairs with all nodes already seen
                a += (rs * count);
                rs += count;
            }

            ans[i] = a;
        }

        return ans;
    }
};
