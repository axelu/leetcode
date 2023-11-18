
// 2846. Minimum Edge Weight Equilibrium Queries in a Tree
// https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/

class Solution {
private:
    vector<int> ans;
    int cnt[10000][27];
    int t[27];
    
    void dfs(vector<pair<int,int>> g[], int u, int src, int t[]) {
        // record count of weights for every edge between root and u
        for(int i = 1; i < 27; ++i)
            cnt[u][i] = t[i];
        
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i].first;
            if( v == src )
                continue;
            int weight = g[u][i].second;
            ++t[weight];
            dfs(g,v,u,t);
            // backtrack
            --t[weight];
        }
        
        return;
    }
    
    // Lowest Common Ancestor (LCA) in N-ary tree
    int LCA(vector<pair<int,int>> g[], int root, int src, int a, int b) {
        if( root == a || root == b )
            return root;

        int lft_lca = -1;
        int rgt_lca = -1;

        for(int i = 0; i < g[root].size(); ++i) {
            int child = g[root][i].first;
            if( child == src )
                continue;
            
            if( lft_lca == -1 ) {
                lft_lca = LCA(g,child,root,a,b);
            
            } else {
                rgt_lca = LCA(g,child,root,a,b);
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

    int solve(int a, int b, int lca) {
        memset(t,0,sizeof t);
        int edge_cnt = 0;      // count of edges between a and b
        int mx_cnt_weight = 0; // dominant edge weight of all edges between a and b

        for(int i = 1; i < 27; ++i) {
            t[i] = cnt[a][i] + cnt[b][i] - 2* cnt[lca][i];
            if( t[i] != 0 ) {
                edge_cnt += t[i];
                mx_cnt_weight = max(mx_cnt_weight, t[i]);
            }
        }
        
        return edge_cnt - mx_cnt_weight;
    }    
        
    // Lowest Common Ancestor - Tarjan's off-line algorithm
    // https://cp-algorithms.com/graph/lca_tarjan.html
    vector<vector<pair<int,int>>> _queries;
    vector<int> ancestor;
    vector<bool> visited;
    
    int * parent;

    int findRoot(int i) {
		// chase parent of current element until it reaches root

        while(parent[i] != i) {
            // path compression
            // set each i to point to its grandparent
            // (thereby halving the path length), where i
            // is the node which comes in between path,
            // while computing root
            parent[i] = parent[parent[i]] ;
            i = parent[i];
        }
		return i;
	}

	void unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return;
		parent[c] = p;
	}
    
    void dfs(vector<pair<int,int>> g[], int v) {
        visited[v] = true;
        ancestor[v] = v;
        for(auto& p: g[v]) {
            int u = p.first;
            if( !visited[u] ) {
                dfs(g,u);
                unite(v,u);
                ancestor[findRoot(v)] = v;
            }
        }
        for(auto& p: _queries[v]) {
            int other_node = p.first;
            int q_idx = p.second;
            
            if( ans[q_idx] == -1 && visited[other_node] ) {
                int _lca = ancestor[findRoot(other_node)];
                // cout << "LCA of " << v << " and " << other_node << " is " << _lca << ".\n";            
                ans[q_idx] = solve(v,other_node,_lca);
            }
        }
    }
    
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int m = queries.size();
        ans.resize(m);ans.assign(m,-1);
        
        // root the tree in an arbitrary node, let's say 0
        // for each node, record the count of weight from root to said node
        // to answer queries, we use the recorded weight counts and 
        // subtract the weight count from root to their lowest common ancestor (LCA) twice
        
        vector<pair<int,int>> g[n];
        for(auto& edge: edges) {
            g[edge[0]].push_back({edge[1],edge[2]});
            g[edge[1]].push_back({edge[0],edge[2]});
        }
        
        memset(cnt,0,sizeof cnt);
        memset(t,0,sizeof t);
        dfs(g,0,-1,t);
        
        /*
        for(int k = 0; k < m; ++k) {
            int a = queries[k][0];
            int b = queries[k][1];
            
            // get lowest common ancestor (LCA) for a, b
            int _lca = LCA(g,0,-1,a,b);
            ans[k] = solve(a,b,_lca);
        }
        
        return ans;
        */
        
        int _parent[n]; parent = _parent;
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself

        _queries.resize(n);
        for(int k = 0; k < m; ++k) {
            int a = queries[k][0];
            int b = queries[k][1];
            _queries[a].push_back({b,k});
            _queries[b].push_back({a,k});
        }

        ancestor.resize(n);
        visited.assign(n, false);
        dfs(g,0);
        
        return ans;
    }
};



// passes 723/733 test cases, then TLE 9/22/2023
// slow part is LCA determination


class Solution {
private:
    int cnt[10000][27];

    void dfs(vector<pair<int,int>> g[], int u, int src, int t[]) {
        // record count of weights for every edge between root and u
        for(int i = 1; i < 27; ++i)
            cnt[u][i] = t[i];

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i].first;
            if( v == src )
                continue;
            int weight = g[u][i].second;
            ++t[weight];
            dfs(g,v,u,t);
            // backtrack
            --t[weight];
        }

        return;
    }

    // Lowest Common Ancestor (LCA) in N-ary tree
    int LCA(vector<pair<int,int>> g[], int root, int src, int a, int b) {
        if( root == a || root == b )
            return root;

        int lft_lca = -1;
        int rgt_lca = -1;

        for(int i = 0; i < g[root].size(); ++i) {
            int child = g[root][i].first;
            if( child == src )
                continue;

            if( lft_lca == -1 ) {
                lft_lca = LCA(g,child,root,a,b);

            } else {
                rgt_lca = LCA(g,child,root,a,b);
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
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int m = queries.size();
        vector<int> ans(m);

        // root the tree in an arbitrary node, let's say 0
        // for each node, record the count of weight from root to said node
        // to answer queries, we use the recorded weight counts and
        // subtract the weight count from root to their lowest common ancestor (LCA) twice

        vector<pair<int,int>> g[n];
        for(auto& edge: edges) {
            g[edge[0]].push_back({edge[1],edge[2]});
            g[edge[1]].push_back({edge[0],edge[2]});
        }

        memset(cnt,0,sizeof cnt);
        int t[27]; memset(t,0,sizeof t);
        dfs(g,0,-1,t);

        for(int k = 0; k < m; ++k) {
            int a = queries[k][0];
            int b = queries[k][1];

            // get lowest common ancestor (LCA) for a, b
            int _lca = LCA(g,0,-1,a,b);

            memset(t,0,sizeof t);
            int edge_cnt = 0;      // count of edges between a and b
            int mx_cnt_weight = 0; // dominant edge weight of all edges between a and b
            for(int i = 1; i < 27; ++i) {
                t[i] = cnt[a][i] + cnt[b][i] - 2* cnt[_lca][i];
                if( t[i] != 0 ) {
                    edge_cnt += t[i];
                    mx_cnt_weight = max(mx_cnt_weight, t[i]);
                }
            }

            ans[k] = edge_cnt - mx_cnt_weight;
        }

        return ans;
    }
};
