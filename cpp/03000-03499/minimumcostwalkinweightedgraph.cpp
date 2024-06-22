
// 3108. Minimum Cost Walk in Weighted Graph
// https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/






class Solution {
private:
    // disjoint-set path compression size
    int * parent;
    int * size;

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

    void dfs(vector<vector<int>> g[], int u, int src, bool seen[], int& a) {
        seen[u] = true;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i][0];
            if( v == src )
                continue;
            int weight = g[u][i][1];
            a &= weight;

            if( seen[v] )
                continue;
            unite(u, v);
            dfs(g, v, u, seen, a);
        }

        return;
    }

public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        vector<vector<int>> g[n];
        for(auto& edge: edges) {
            g[edge[0]].push_back({edge[1],edge[2]});
            g[edge[1]].push_back({edge[0],edge[2]});
        }

        int _parent[n]; parent = _parent;
        int _size[n]; size = _size;
        int w[n];
        for(int i = 0; i < n; ++i) {
            parent[i] = i;
            size[i] = 1;
        }

        bool seen[n];memset(seen,false,sizeof seen);
        for(int u = 0; u < n; ++u) {
            if( seen[u] )
                continue;
            int a = 131071; // binary 11111111111111111
            dfs(g, u, -1, seen, a);
            int root = find(u);
            w[root] = a;
        }

        int q_sz = query.size();
        vector<int> ans(q_sz,-1);
        for(int i = 0; i < q_sz; ++i) {
            int u = query[i][0];
            int v = query[i][1];
            int root_u = find(u); // cout << "u " << u << " root_u " << root_u << endl;
            int root_v = find(v); // cout << "v " << v << " root_v " << root_v << endl;
            if( root_u == root_v )
                ans[i] = w[root_u];
        }

        return ans;
    }
};
