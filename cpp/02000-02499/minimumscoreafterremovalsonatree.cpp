
// 2322. Minimum Score After Removals on a Tree
// https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/



class Solution {
private:
    int dfs(vector<int> g[],
            int u,
            int parent,
            vector<int>& nums,
            unordered_set<int>& path,
            unordered_set<int> ancestors[],
            int cxor[]) {

        // record our ancestors = the path that got us here
        ancestors[u] = path;

        // add current node to path
        path.insert(u);

        int uxor = nums[u];

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            // don't go back to our parent
            if( v != parent )
                uxor ^= dfs(g,v,u,nums,path,ancestors,cxor);
        }

        // backtrack
        path.erase(u);

        return cxor[u] = uxor;
    }
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        // input is an 'undirected tree' with nodes 0 to n - 1 and n - 1 edges
        // let's build an undirected 'graph'
        int n = nums.size();
        vector<int> g[n];
        for(auto& v : edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        // as our input is a tree, we need to root the tree.
        // use any arbitrary node as the root, like node 0

        unordered_set<int> ancestors[n];      // ancestors of each node i
        int cxor[n];                          // xor for subtree rooted in i including i
        unordered_set<int> path;
        dfs(g,0,-1,nums,path,ancestors,cxor); // start at node 0, our arbitrary root, which doesn't have a parent

        // debug
        /*
        for(int i = 0; i < n; ++i) {
            cout << i << ": ";
            for(int x : ancestors[i] )
                cout << x << " ";
            cout << endl;
        }
        for(int i = 0; i < n; ++i)
            cout << i << ": " << cxor[i] << endl;
        */

        // if we remove two edges, we are breaking the tree into three connected components
        // as we rooted the tree in node 0, we will look at an edge {A,B} such that A is the parent (ancestor) of B,
        // respectively an edge {C,D} such that C is the parent (ancestor) of D.
        // so that after removing edge {A,B} we have a subtree rooted in B formed.
        // after removing a second edge {C,D} we have a subtree rooted in D AND the remaining tree rooted in root 0,
        // for the case that edge {C,D} is in the subtree of edge {A,B}.
        // those are our three components after removing two edges.
        // the two edges we are removing are somewhere in our tree
        // in order to calculate xor for each of the created three connected components, if we fix one edge
        // and iterate over all other edges, then these two edges can have the following relation to each other:
        //    edge2 is in the subtree of edge1
        //    edge1 is in the subtree of edge2
        //    edge1 and edge2 are in different subtrees from root

        // arrange all edges so that edge[i][0] is parent of edge[i][1] when tree routed at 0
        for(auto& v : edges)
            if( ancestors[v[0]].count(v[1]) ) {
                // cout << "swapping edge org " << v[0] << " " << v[1];
                int t = v[1];
                v[1] = v[0];
                v[0] = t;
                // cout << " new " << v[0] << " " << v[1] << endl;
            }

        int ans = INT_MAX;
        int A; // endpoint edge[i] that is parent of B when tree rooted at 0
        int B; // endpoint edge[i] that is child of A when tree rooted at 0
        int C; // endpoint edge[j] that is parent of D when tree rooted at 0 (Note that B and C could be same node)
        int D; // endpoint edge[j] that is child of C
        for(int i = 0; i < n-1; ++i) {
            A = edges[i][0];
            B = edges[i][1];
            // cout << "edge i " << i << " A " << A << " B " << B << endl;
            for(int j = 0; j < n-1; ++j) {
                if( j == i )
                    continue;

                C = edges[j][0];
                D = edges[j][1];
                // cout << "  edge j " << j << " C " << C << " D " << D << endl;

                int xorD; // xor of subtree rooted in D
                int xorB; // xor of subtree rooted in B
                int xor0; // xor of remaining tree rooted at root 0
                if( ancestors[D].count(B) ) {
                    // cout << "  edge[j] is in subtree of edge[i]" << endl;
                    xorD = cxor[D];
                    xorB = cxor[B] ^ xorD;
                } else if( ancestors[B].count(D) ) {
                    // cout << "  edge[i] is in subtree of edge[j]" << endl;
                    xorB = cxor[B];
                    xorD = cxor[D] ^ xorB;
                } else {
                    // cout << "  edge[i] and edge[j] in different subtree" << endl;
                    xorB = cxor[B];
                    xorD = cxor[D];
                }
                xor0 = cxor[0] ^ xorD ^ xorB;
                int t = max({xorD,xorB,xor0}) - min({xorD,xorB,xor0});
                // cout << "    xorB " << xorB << " xorD " << xorD << " xor0 " << xor0 << " t " << t << endl;
                ans = min(ans,t);
            }
        }

        return ans;
    }
};
