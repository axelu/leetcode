
// 3772. Maximum Subgraph Score in a Tree
// https://leetcode.com/problems/maximum-subgraph-score-in-a-tree/




class Solution {
private:
    vector<int> g[100000]; // undirected graph
    // vector<vector<int>> g; // undirected graph
    int best[100000];
    // vector<int> best;
    map<int,int> bestadj[100000];
    // vector<map<int,int>> bestadj;

    int dfs(int u, int src, vector<int>& good) {
        // if src == -1, then we must include us in the score!
        // otherwise our max could be 0 not include us or any
        //    of our subgraph's aka children

        // return the best score to src of me and all my other children
        auto it = g[u].begin();
        while( it != g[u].end() ) {
            int v = *it;
            if( v != src ) {
                int t = dfs(v, u, good);
                best[u] += max(0, t);
                // mark as processed by removing from adjencency list
                bestadj[u][v] = max(0, t);
                it = g[u].erase(it);
            } else {
                ++it;
            }
        }

        int ret = best[u] + (good[u] ? 1 : -1);

        // subtract src from best score
        if( src != -1 ) {
            return ret - bestadj[u][src];
        }

        return ret;
    }

public:
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good) {
        // 2 <= n <= 1e5; edges.length == n - 1

        // g.resize(n);
        // best.resize(n);
        // bestadj.resize(n);

        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];

            g[u].push_back(v);
            bestadj[u].insert({v, 0});

            g[v].push_back(u);
            bestadj[v].insert({u, 0});
        }

        vector<int> ans(n);
        memset(best, 0, sizeof best);
        for(int i = 0; i < n; ++i) {
            int t = dfs(i, -1, good);
            ans[i] = t;
        }

        return ans;
    }
};
