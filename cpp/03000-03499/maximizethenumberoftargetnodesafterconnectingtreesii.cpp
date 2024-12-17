
// 3373. Maximize the Number of Target Nodes After Connecting Trees II
// https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/








class Solution {
private:
    // for each node, stores the result of even/odd response
    // for the nodes it is connected to
    vector<unordered_map<int,pair<int,int>>> res;

    // for each node, stores sum of even/odd distance nodes
    // from all the nodes it is connected to
    vector<pair<int,int>> sum;


    pair<int,int> rec(vector<vector<int>>& t, int u, int src) {
        // even, odds
        // number of nodes in the subtree of u that have an even distance to u
        // number of nodes in the subtree of u that have an odd distance to u

        // a node connecting to us, if it has x decendants in its subtree with even distance
        // because of the edge to us, those become odd distances
        // vice versa for odd distances, those become even distances


        if( !t[u].empty() ) {
            // we have at least one subtree [still] to explore

            // int ret_even = 1; // our current node is at distance 0 (even)
            int even = 0;
            int odd = 0;

            for(auto it = t[u].begin(); it != t[u].end(); ) {
                int v = *it;
                if( v == src ) {
                    ++it;
                    continue;
                }

                auto p = rec(t, v, u); // even, odds
                // ret_even += p.second;
                // ret_odd  += p.first;

                even += p.second;
                odd  += p.first;

                res[u][v] = {p.first, p.second};

                it = t[u].erase(it);
            }

            sum[u].first  += even;
            sum[u].second += odd;

        }

        // on purpose reversed
        int ret_even = sum[u].first - res[u][src].second + 1; // + 1 // our current node is at distance 0 (even)
        int ret_odd  = sum[u].second - res[u][src].first;

        return {ret_even, ret_odd};
    }

public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;

        res.resize(max(n, m)+1);
        sum.resize(max(n, m));


        vector<vector<int>> t2(m);
        for(auto& edge: edges2) {
            t2[edge[0]].push_back(edge[1]);
            t2[edge[1]].push_back(edge[0]);
        }

        // for tree 2 we are only interested in the max odd
        int mx = 1;
        for(int u = 0; u < m; ++u) {
            auto p = rec(t2, u, m);
            mx = max(mx, p.second);
        }
        // cout << "mx " << mx << endl;

        // reset
        for(int i = 0; i <= m; ++i)
            res[i].clear();
        for(int i = 0; i < m; ++i)
            sum[i] = {0, 0};

        vector<vector<int>> t1(n);
        for(auto& edge: edges1) {
            t1[edge[0]].push_back(edge[1]);
            t1[edge[1]].push_back(edge[0]);
        }

        vector<int> ans(n);
        for(int u = 0; u < n; ++u) {
            auto p = rec(t1, u, n);
            ans[u] = p.first + mx;
        }

        return ans;
    }
};
