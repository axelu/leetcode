
// 3558. Number of Ways to Assign Edge Weights I
// https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/





// initialize once
long mem[100001][2];
bool init = false;

class Solution {
private:
    const long mod = 1000000007;

    int dfs(vector<vector<int>>& t, int u, int src, int depth) {
        int ret = depth;
        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;
            ret = max(ret, dfs(t, v, u, depth+1));
        }
        return ret;
    }

    long rec(int i, int parity, int rem) {
        if( rem == 0 )
            return parity == 1;

        if( mem[i][parity] != -1 )
            return mem[i][parity];

        long ret = 0;

        // we have a choice
        //    make the next edge 2 aka even
        //    make the next edge 1 aka odd

        //    even even even    0 0 0
        //    even odd  odd     0 1 1
        //    odd  even odd     1 0 1
        //    odd  odd  even    1 1 0

        ret = (ret + rec(i+1, parity ^ 0, rem - 1)) % mod;
        ret = (ret + rec(i+1, parity ^ 1, rem - 1)) % mod;

        return mem[i][parity] = ret;
    }

public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        if( init == false ) {
            init = true;
            memset(mem,-1,sizeof mem);
            rec(0, 0, 100000);
        }

        // undirected tree, nodes 1..n, rooted at node 1
        // edges.size() = n - 1
        int n = edges.size() + 1;

        if( n == 2 )
            return 1;

        vector<vector<int>> t(n+1);
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        int max_depth = dfs(t, 1, -1, 0);
        // cout << "max_depth " << max_depth << endl;

        return mem[100000-max_depth][0];
    }
};
