
// 2581. Count Number of Possible Root Nodes
// https://leetcode.com/problems/count-number-of-possible-root-nodes/




class Solution {
private:
    int dfs(vector<pair<int,int>> g[], int u, int src, unordered_set<int> pcguesses[]) {

        // we know that Bob's guesses are valid edges, hence we assume all
        // his guesses for the current node as parent are true
        // but if his guess included the src, then we need to discount that
        int me = pcguesses[u].size();
        if( pcguesses[u].find(src) != pcguesses[u].end() )
            --me;

        for(int i = 0; i < g[u].size(); ++i) {
            // g[u][i].first is v
            // g[u][i].second is contribution of v as child
            int v = g[u][i].first;
            if( v == src )
                continue;

            if( g[u][i].second == -1 )
                g[u][i].second = dfs(g,v,u,pcguesses);

            me += g[u][i].second;
        }

        return me;
    }

public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;

        vector<pair<int,int>> g[n]; // undirected graph
                                    // pair.first: child, pair.second: answer when explored as child
        for(auto& v: edges) {
            g[v[0]].push_back({v[1],-1});
            g[v[1]].push_back({v[0],-1});
        }

        unordered_set<int> pcguesses[n]; // key: parent, value: list of children
        for(auto& v: guesses)
            pcguesses[v[0]].insert(v[1]);

        int ans = 0;
        // baseline with node 0 as root
        for(int root = 0; root < n; ++root) {
            int t = dfs(g,root,-1,pcguesses);
            if( t >= k )
                ++ans;
        }

        return ans;
    }
};
