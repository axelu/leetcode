
// 3559. Number of Ways to Assign Edge Weights II
// https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/

// passes with path_u_to_root as unordered_set<int> and as array[100001]
// makes seemingly no difference in runtime though


// initialize once
long mem[100001][2];
bool init = false;

class Solution {
    const long mod = 1000000007;

    int depths[100001];
    int parent[100001];

    void dfs(vector<vector<int>>& t, int u, int src, int depth) {
        depths[u] = depth;
        parent[u] = src;
        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;
            dfs(t, v, u, depth+1);
        }
        return;
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

    // Lowest Common Ancestor (LCA) in N-ary tree
    int LCA(vector<vector<int>>& t, int root, int src, int a, int b) {
        if( root == a || root == b )
            return root;

        int lft_lca = -1;
        int rgt_lca = -1;

        for(int i = 0; i < t[root].size(); ++i) {
            int child = t[root][i];
            if( child == src )
                continue;

            if( lft_lca == -1 ) {
                lft_lca = LCA(t,child,root,a,b);

            } else {
                rgt_lca = LCA(t,child,root,a,b);
                if( rgt_lca != -1 )
                    break;
            }
        }

        // if both of the above calls return something other than -1,
        // then one key is present in one subtree and
        // other key is present in other subtree, hence the
        // current node is the Lowest Common Ancestor (LCA) to both keys
        if( -1 != lft_lca && -1 != rgt_lca )
            return root;

        // else check if left subtree or right subtree is LCA
        return lft_lca;
    }


public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        if( init == false ) {
            init = true;
            memset(mem,-1,sizeof mem);
            rec(0, 0, 100000);
        }

        // undirected tree, nodes 1..n, rooted at node 1
        // edges.size() = n - 1
        int n = edges.size() + 1; cout << "n " << n << endl;

        vector<vector<int>> t(n+1);
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        dfs(t, 1, -1, 0);

        // process queries
        int q_sz = queries.size();
        vector<vector<int>> _queries(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int v = queries[i][1];
            if( v < u )
                swap(u,v);
            _queries[i] = {u,v,i};
        }
        sort(_queries.begin(), _queries.end(), [](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0];
        });

        vector<int> ans(q_sz, 0);
        int pre = -1;
        // unordered_set<int> path_u_to_root; // path from u to root aka to node 1
        int path_u_to_root[100001];
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int v = queries[i][1];

            if( u == v ) {
                // ans[i] = 0;
                continue;
            }

            if( u == 1 ) {
                // every v is a descendant of node 1
                ans[i] = mem[100000 - depths[v]][0];
                continue;
            }

            if( u != pre ) {
                // we are starting to process queries for a new u
                // path_u_to_root.clear();
                memset(path_u_to_root,-1,sizeof path_u_to_root);
                int c = u;
                while( parent[c] != -1 ) {
                    // path_u_to_root.insert(parent[c]);
                    path_u_to_root[parent[c]] = 1;
                    c = parent[c];
                }
                pre = u;
            }

            // if v is in the path from u to root aka u to node 1,
            // then u is a descendant of v
            // auto fv = path_u_to_root.find(v);
            // if( fv != path_u_to_root.end() ) {
            if( path_u_to_root[v] != -1 ) {
                // v is an ancestor of u
                int dist = depths[u] - depths[v];
                ans[i] = mem[100000 - dist][0];
                continue;  
            }

            // construct the path from v to root aka to node 1
            // check along the way for u in the path, or a common node
            int p = v;
            while( parent[p] != -1 ) {
                p = parent[p];
                if( p == u ) {
                    // v is a descendant of u respectively
                    // u is an ancestor of v
                    int dist = depths[v] - depths[u];
                    ans[i] = mem[100000 - dist][0];
                    break;
                }
                // auto fp = path_u_to_root.find(p);
                // if( fp != path_u_to_root.end() ) {
                if( path_u_to_root[p] != -1 ) {
                    // p is the LCA of u and v
                    int dist = depths[u] - depths[p];
                    dist += depths[v] - depths[p];
                    ans[i] = mem[100000 - dist][0];
                    break;
                }
            }
        }

        return ans;
    }
};

// passes 581/589 test cases as of 5/26/2025, then TLE


// initialize once
long mem[100001][2];
bool init = false;

class Solution {
    const long mod = 1000000007;

    int depths[100001];

    void dfs(vector<vector<int>>& t, int u, int src, int depth) {
        depths[u] = depth;
        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;
            dfs(t, v, u, depth+1);
        }
        return;
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

    // Lowest Common Ancestor (LCA) in N-ary tree
    int LCA(vector<vector<int>>& t, int root, int src, int a, int b) {
        if( root == a || root == b )
            return root;

        int lft_lca = -1;
        int rgt_lca = -1;

        for(int i = 0; i < t[root].size(); ++i) {
            int child = t[root][i];
            if( child == src )
                continue;

            if( lft_lca == -1 ) {
                lft_lca = LCA(t,child,root,a,b);

            } else {
                rgt_lca = LCA(t,child,root,a,b);
                if( rgt_lca != -1 )
                    break;
            }
        }

        // if both of the above calls return something other than -1,
        // then one key is present in one subtree and
        // other key is present in other subtree, hence the
        // current node is the Lowest Common Ancestor (LCA) to both keys
        if( -1 != lft_lca && -1 != rgt_lca )
            return root;

        // else check if left subtree or right subtree is LCA
        return lft_lca;
    }


public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        if( init == false ) {
            init = true;
            memset(mem,-1,sizeof mem);
            rec(0, 0, 100000);
        }

        // undirected tree, nodes 1..n, rooted at node 1
        // edges.size() = n - 1
        int n = edges.size() + 1;

        vector<vector<int>> t(n+1);
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        dfs(t, 1, -1, 0);

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int v = queries[i][1];

            if( u == v ) {
                ans[i] = 0;
                continue;
            }

            // get lowest common ancestor (LCA) for a, b
            int _lca = LCA(t,1,-1,u,v);

            int dist;
            if( _lca == u ) {
                // u is an ancestor of v
                dist = depths[v] - depths[u];

            } else if( _lca == v ) {
                // v is an ancestor of u
                dist = depths[u] - depths[v];

            } else {
                dist = depths[u] - depths[_lca];
                dist += depths[v] - depths[_lca];
            }

            ans[i] = mem[100000 - dist][0];
        }

        return ans;
    }
};
