
// 2242. Maximum Score of a Node Sequence
// https://leetcode.com/problems/maximum-score-of-a-node-sequence/




class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n = scores.size();

        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            return a[1] > b[1];
        };

        vector<array<int,2>> g[n]; // undirected graph

        // pass 1
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            g[u].push_back({v,scores[v]});
            sort(g[u].begin(),g[u].end(),cmp);
            if( g[u].size() > 4 )
                g[u].pop_back();

            g[v].push_back({u,scores[u]});
            sort(g[v].begin(),g[v].end(),cmp);
            if( g[v].size() > 4 )
                g[v].pop_back();
        }

        int ans = -1;

        // pass 2
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            int t = -1;
            for(auto& adjU : g[u]) {
                if( adjU[0] == v )
                    continue;
                for(auto& adjV : g[v]) {
                    if( adjV[0] == u )
                        continue;
                    if( adjU[0] != adjV[0] )
                        t = max(t, adjU[1] + adjV[1]);
                }
            }

            if( t != -1 )
                ans = max(ans, scores[u] + scores[v] + t);
        }

        return ans;
    }
};
