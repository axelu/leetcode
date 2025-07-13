
// 3608. Minimum Time for K Connected Components
// https://leetcode.com/problems/minimum-time-for-k-connected-components/

class Solution {
   vector<int> parent;

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
    int minTime(int n, vector<vector<int>>& edges, int k) {
        parent.resize(n);

        // quick check
        // how many cc are there to begin with?
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only
        int cc  = n; // number of connected components

        int edges_sz = edges.size();
        for(int i = 0; i < edges_sz && cc >= k; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            int time = edges[i][2];

            if( findRoot(u) != findRoot(v) ) {
                unite(u, v);
                --cc;
            }
        }

        if( cc >= k )
            return 0;

        // reset
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only
        cc  = n; // number of connected components

        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b){
            return a[2] > b[2];
        });

        int t = edges[0][2];
        int ans = t;

        for(int i = 0; i < edges_sz && cc >= k; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            int time = edges[i][2];

            if( time < t && cc >= k ) {
                ans = time;
                t = time;
            }

            if( findRoot(u) != findRoot(v) ) {
                unite(u, v);
                --cc;
            }
        }

        return ans;
    }
};
