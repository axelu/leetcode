
// 3787. Find Diameter Endpoints of a Tree
// https://leetcode.com/problems/find-diameter-endpoints-of-a-tree/



class Solution {
private:
    void dfs(vector<vector<int>>& g, int u, int src, int depth, vector<int>& farthest) {
        // farthest[0] is the max depth seen so far
        if( depth > farthest[0] ) {
            farthest.clear();
            farthest.push_back(depth);
            farthest.push_back(u);
        } else if( depth == farthest[0] ) {
            farthest.push_back(u);
        }

        for(int v: g[u])
            if( v != src )
                dfs(g, v, u, depth+1, farthest);

        return;
    }

public:
    string findSpecialNodes(int n, vector<vector<int>>& edges) {
        // 2 <= n <= 1e5
        // undirected tree with n nodes, numbered from 0 to n - 1.
        // array edges of length n - 1,
        // edges[i] = [ai, bi] edge between nodes ai and bi

        if( n == 2 )
            return "11";

        // a special node is an endpoint
        // but not every endpoint is a special node
        // worst cases
        //    star topology -> n-1 endpoints
        //    line topology -> 2 endpoints
        // an endpoint is a node with a degree of 1 aka 1 edge

        vector<vector<int>> g(n, vector<int>());
        for(vector<int>& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // pass 1
        // root the tree in an arbitrary node and find
        // the nodes with longest path from our root
        // collect those nodes into start
        vector<int> start{-1};
        dfs(g, 0, -1, 0, start);

        // pass 2
        // foreach node in start, get the other end(s)
        // if start node is already in other end, then we can skip
        string ans(n,'0');
        for(int i = 1; i < start.size(); ++i) {
            if( ans[start[i]] == '1' )
                continue;
            ans[start[i]] = '1';
            vector<int> other{-1};
            dfs(g, start[i], -1, 0, other);
            for(int j = 1; j < other.size(); ++j)
                ans[other[j]] = '1';
        }

        return ans;
    }
};
