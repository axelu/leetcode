
// 1135. Connecting Cities With Minimum Cost
// https://leetcode.com/problems/connecting-cities-with-minimum-cost/



// see also https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/
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
    int minimumCost(int n, vector<vector<int>>& connections) {
        // n cities numbered from 1 to n
        int i;

        // minimum spanning tree (Kruskal's algorithm)

        // connections[i] = [city1, city2, cost] is basically an edge list
        // sort edgeList by cost of edges ascending aka lowest cost edge first
        sort(connections.begin(),connections.end(),[](const vector<int>& a, const vector<int>& b){
           return  a[2]<b[2];
        });

        int _parent[n+1]; parent = _parent;
        for(i = 0; i <= n; ++i)
            parent[i] = i; // initially each node is connected to itself only


        // as our edgeList is sorted by cost and starts with the cheapest edge, our graph
        // will only include the cheapest edges that connect two vertices.
        int cc  = n; // number of connected components
        int ans = 0;
        for(i = 0; i < connections.size(); ++i) {
            if( findRoot(connections[i][0]) != findRoot(connections[i][1]) ) {
                unite(connections[i][0],connections[i][1]);
                ans += connections[i][2];
                --cc;
            }
        }

        return cc == 1 ? ans : -1;
    }
};
