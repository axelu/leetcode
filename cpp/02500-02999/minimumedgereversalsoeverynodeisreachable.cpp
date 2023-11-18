
// 2858. Minimum Edge Reversals So Every Node Is Reachable
// https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable/





class Solution {
private:

    unordered_map<long,int> mem;

    int dfs(vector<pair<int,int>> g[], int u, int src) {
        // cout << "dfs u " << u << " src " << src << endl;
        long key = -1;
        if( src != -1 ) {
            key = ((long)u<<17) + src;
            auto f = mem.find(key);
            if( f != mem.end() ) {
                // cout << "hit" << endl;
                return f->second;
            }
        }

        int ret = 0;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i].first;
            if( v == src )
                continue;
            int weight = g[u][i].second;
            ret += weight + dfs(g,v,u);
        }

        if( key != -1 )
            mem[key] = ret;

        return ret;
    }

public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        vector<int> ans(n);

        vector<pair<int,int>> g[n];
        for(auto& edge: edges) {
            g[edge[0]].push_back({edge[1],0});
            g[edge[1]].push_back({edge[0],1});
        }

        for(int u = 0; u < n; ++u)
            ans[u] = dfs(g,u,-1);

        return ans;
    }
};
