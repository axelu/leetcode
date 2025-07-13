
// 3600. Maximize Spanning Tree Stability with Upgrades
// https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/



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
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        // quick check: if number of must-include edges > n-1
        // then we have no solution
        // 1st check if all must-include edges (if any)
        // form a cycle, if so, we have no solution
        // if no cycle and number of must-include edges == n-1
        // we have a solution already, which is minimum
        // strength edge of all must-include edges
        // otherwise, sort the remaining edges by strength
        // descending and add them till we have a spanning tree
        // keep track of min edge in tree (our added edges * 2)
        // keep track of number of connected components

        // spanning tree (Kruskal's algorithm)
        parent.resize(n);
        for(int i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        int cc  = n; // number of connected components

        int edges_sz = edges.size();

        int min_stability = INT_MAX; // 1 <= s <= 1e5

        // process 'must include' edges
        for(int i = 0; i < edges_sz; ++i) {
            if( edges[i][3] != 1 )
                continue;

            int u = edges[i][0];
            int v = edges[i][1];
            int strength = edges[i][2];

            if( findRoot(u) != findRoot(v) ) {
                unite(u, v);
                --cc;
                min_stability = min(min_stability, strength);
            } else {
                return -1;
            }
        }

        if( cc == 1 )
            return min_stability;

        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b){
            return a[2] > b[2];
        });

        // process 'optional' edges
        multiset<int> ms;
        for(int i = 0; i < edges_sz; ++i) {
            if( edges[i][3] != 0 )
                continue;

            int u = edges[i][0];
            int v = edges[i][1];
            int strength = edges[i][2];

            if( findRoot(u) != findRoot(v) ) {
                unite(u, v);
                --cc;
                ms.insert(strength);
            }
        }

        if( cc != 1 )
            return -1;

        // edge case
        if( k == 0 )
            min_stability = min(min_stability, *(ms.begin()));

        // we can multiply the k-smallest strengths by 2
        auto it = ms.begin();
        for(; it != ms.end() && k > 0; ++it) {
            int strength = *it * 2;
            min_stability = min(min_stability, strength);
            --k;
            if( k == 0 && next(it) != ms.end() )
                min_stability = min(min_stability, *(next(it)));
        }

        return min_stability;
    }
};
