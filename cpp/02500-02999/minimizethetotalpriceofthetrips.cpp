
// 2646. Minimize the Total Price of the Trips
// https://leetcode.com/problems/minimize-the-total-price-of-the-trips/


class Solution {
private:
    void dfs(unordered_set<int> g[], int u, int src, unordered_set<int> path[]) {
        if( src != -1 )
            path[u] = path[src]; // path so far
        
        path[u].insert(u);
        
        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = *it;
            if( v == src )
                continue;
            dfs(g,v,u,path);
        }
    }
    
    // Lowest Common Ancestor (LCA) in N-ary tree
    int LCA(unordered_set<int> g[], int root, int src, int a, int b) {
        if( root == a || root == b )
            return root;

        int lft_lca = -1;
        int rgt_lca = -1;

        for(auto it = g[root].begin(); it != g[root].end(); ++it) {
            int child = *it;
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
    
    int mem[50][2];
    
    // TODO only need to do this for nodes involved in trips
    int rec(unordered_set<int> g[], int u, int src, int half, int cnt[], vector<int>& price) {
        // half is either 0 or 1, if 1 then we can half ourselfs, but we don't have to
        //                        if 0 then we must not half ourselfs
        
        if( mem[u][half] != -1 )
            return mem[u][half];        
        
        if( mem[u][0] == -1 ) {
            mem[u][0] = cnt[u] * price[u];
            for(auto it = g[u].begin(); it != g[u].end(); ++it) {
                int v = *it;
                if( v == src )
                    continue;
                mem[u][0] += rec(g,v,u,1,cnt,price);
            }
        }
        if( cnt[u] == 0 )
            return mem[u][1] = mem[u][0];
        if( half == 0 )
            return mem[u][0];
        
        int ret1 = cnt[u] * (price[u]/2);
        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = *it;
            if( v == src )
                continue;
            ret1 += rec(g,v,u,0,cnt,price);
        }
        
        return mem[u][1] = min(mem[u][0],ret1);
    }

    
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        // arbitrarily root the tree, lets say in node 0
        // record path from root to every node
        // for each trip, record all nodes (via lowest common ancestor lca)
        // then we know the frequency of all nodes for all trips and
        // we can somehow calculate the answer
        
        unordered_set<int> g[n];
        for(auto& edge: edges) {
            g[edge[0]].insert(edge[1]);
            g[edge[1]].insert(edge[0]);
        }
        
        unordered_set<int> path[n];
        dfs(g,0,-1,path);
        
        /*
        for(int i = 0; i < n; ++i) {
            cout << "path 0 to " << i << ": ";
            for(auto it = path[i].begin(); it != path[i].end(); ++it)
                cout << *it << " ";
            cout << endl;
        }
        */
        
        int cnt[n];memset(cnt,0,sizeof cnt); // number of times each node is passed for all trips
        
        for(auto& trip: trips) {
            int a = trip[0];
            int b = trip[1];
            int _lca = LCA(g,0,-1,a,b);
            
            // TODO we don't need to even temporarily persist pathab, we can just record the 
            //      frequency directly
            unordered_set<int> pathab = path[a];
            for(int hop: path[b]) {
                if( hop == _lca )
                    continue;
                auto p = pathab.insert(hop);
                if( !p.second )
                    pathab.erase(hop);
            }
            /*
            cout << "trip from " << a << " to " << b << endl;
            for(auto it = pathab.begin(); it != pathab.end(); ++it)
                cout << *it << " ";
            cout << endl;
            */
            for(auto it = pathab.begin(); it != pathab.end(); ++it)
                ++cnt[*it];
        }
        
        memset(mem,-1,sizeof mem);
        return rec(g,0,-1,1,cnt,price);
    }
};
