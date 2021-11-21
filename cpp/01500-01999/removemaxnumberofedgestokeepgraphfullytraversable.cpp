
// 1579. Remove Max Number of Edges to Keep Graph Fully Traversable
// https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/





class Solution {
private:
    int * parent;

    // disjoint-set union-find
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


public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        // n nodeds from 1 to n
        int i;

        // sort edges by type with type 3 first, then 2 and lastly 1:
        //    Type 1: Can be traversed by Alice only.
        //    Type 2: Can be traversed by Bob only.
        //    Type 3: Can by traversed by both Alice and Bob.

        sort(edges.begin(),edges.end(),[](const vector<int>& a, const vector<int>& b){
           return  a[0]>b[0];
        });

        // maintain two sets of "parents", one for Alice and one for Bob
        int alice_parent[n+1];
        int bob_parent[n+1];
        for(i = 0; i <= n; ++i)
            alice_parent[i] = i; // initially each node is connected to itself only

        int alice_cc  = n;  // number of connected components
        int bob_cc = n;     // number of connected components

        int ans = 0;


        // process type 3 edges (Bob and Alice)
        parent = alice_parent;
        for(i = 0; i < edges.size(); ++i) {
            if( edges[i][0] != 3 )
                break;
            if( findRoot(edges[i][1]) != findRoot(edges[i][2]) ) {
                unite(edges[i][1],edges[i][2]);
                ++ans;
                --alice_cc;
                --bob_cc;
            }
        }
        copy(alice_parent,alice_parent+n+1,bob_parent);

        // process type 2 edges (Alice)
        for(; i < edges.size(); ++i) {
            if( edges[i][0] != 2 )
                break;
            if( findRoot(edges[i][1]) != findRoot(edges[i][2]) ) {
                unite(edges[i][1],edges[i][2]);
                ++ans;
                --alice_cc;
            }
        }
        if( alice_cc != 1 )
            return -1; // Alice cannot fully traverse the graph

        // process type 1 edges (Bob)
        parent = bob_parent;
        for(; i < edges.size(); ++i) {
            if( findRoot(edges[i][1]) != findRoot(edges[i][2]) ) {
                unite(edges[i][1],edges[i][2]);
                ++ans;
                --bob_cc;
            }
        }
        if( bob_cc != 1 )
            return -1; // Bob cannot fully traverse the graph


        return edges.size()-ans;
    }
};
