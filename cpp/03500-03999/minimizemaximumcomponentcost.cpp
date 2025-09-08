
// 3613. Minimize Maximum Component Cost
// https://leetcode.com/problems/minimize-maximum-component-cost/




class Solution {
private:
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
    int minCost(int n, vector<vector<int>>& edges, int k) {
        // undirected connected graph with n nodes labeled from 0 to n-1

        parent.resize(n);
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        // initially we have n connected components
        int cc = n;
        // we can have at most k connected components
        if( n == 1 || k == n )
            return 0;

        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b){
            return a[2] < b[2];
        });

        int ans = 0;
        int edges_sz = edges.size();
        for(int i = 0; i < edges_sz && cc > k; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            int weight = edges[i][2];

            if( findRoot(u) != findRoot(v) ) {
                unite(u, v);
                --cc;
                ans = max(ans, weight);
            }
        }

        return ans;
    }
};
