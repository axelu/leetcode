
// 3367. Maximize Sum of Weights after Edge Removals
// https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/




class Solution {
private:

    long long mem[100000][2];

    long long rec(vector<vector<pair<int,int>>>& t, int u, int src, int p, int k) {
        // p = 0 means, the node src we came from will NOT consider the edge src->u
        //     meaning edge src->u is removed, and we can keep up to k remaining edges
        // p = 1 means, the node src we came from will consider the edge src->u,
        //     so we can only consider k-1 edges to include

        if( mem[u][p] != -1 )
            return mem[u][p];

         // we have a choice
         //     include edge to child OR
         //     don't include edge to child

         vector<pair<long long, long long>> children(t[u].size());
         for(int i = 0; i < t[u].size(); ++i) {
             int v = t[u][i].first;
             if( v == src )
                 continue;

             long long weight = (long long)t[u][i].second;

             // include edge u -> v
             long long a = weight + rec(t, v, u, 1, k);
             // don't include aka we remove edge u -> v
             long long b = rec(t, v, u, 0, k);

             children[i] = {a,b};
        }
        // we are looking for the edges with the most gain
        sort(children.begin(), children.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b){
            return a.second - a.first < b.second - b.first;
        });

        // in all cases we could remove all edges
        long long possible = 0LL;
        for(auto& ab: children)
            possible += ab.second;

        k -= p; // see above, source did or did not consider edge src->u

        long long ret = possible;

        long long sum = 0LL;
        for(int i = 0; i < k && i < children.size(); ++i) {
            sum += children[i].first;
            possible -= children[i].second;
            ret = max(ret, sum + possible);
        }

        return mem[u][p] = ret;
    }


public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        int n = edges.size() + 1;

        // one way or another, if a given node has more than k edges,
        // we will have to remove those from that node. period.

        // looking at a node in isolation does not work
        // example
        // [[0,1,2],[0,2,3],[0,3,4],[0,4,4],[3,5,5],[3,6,5],[4,7,5],[4,8,5]]
        // 2
        // taking node 0, we would disconnect edge [0,1,2],[0,2,3] because of smallest weight
        // but then we would disconnect the two edes with weight 4 from node 3 and 4
        // which is not ideal, so we need to look at nodes together


        vector<vector<pair<int,int>>> t(n);
        for(int i = 0; i < n-1; ++i) {
            t[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            t[edges[i][1]].push_back({edges[i][0], edges[i][2]});
        }

        memset(mem,-1,sizeof mem);

        // we arbitrarily root the tree at node 0
        return rec(t, 0, -1, 0, k); // we are coming out of nowhere, so no edge to consider
    }
};
