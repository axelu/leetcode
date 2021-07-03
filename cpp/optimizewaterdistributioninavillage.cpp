
// 1168. Optimize Water Distribution in a Village
// https://leetcode.com/problems/optimize-water-distribution-in-a-village/




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
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // n houses numbered from 1 to n in pipes
        // cost to create a well for house i -> wells[i-1] with 1 <= i <= n
        int i;

        // minimum spanning tree (Kruskal's algorithm)

        // we will pretend the well cost is represented by a house 0
        // that is connected to all houses 1 to n and the cost to build
        // a well at house i is the weight of the connection
        for(i = 1; i <= n; ++i)
            pipes.push_back({0,i,wells[i-1]});

        // sort pipes by cost of edges ascending aka cheapest edge first
        sort(pipes.begin(),pipes.end(),[](const vector<int>& a, const vector<int>& b){
           return  a[2]<b[2];
        });

        int _parent[n+1]; parent = _parent;
        for(i = 0; i <= n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        // as our edgeList is sorted by cost and starts with the cheapest edge, our graph
        // will only include the cheapest edges that connect two vertices.
        int cc  = n+1; // number of connected components
        int ans = 0;
        for(i = 0; i < pipes.size(); ++i) {
            if( findRoot(pipes[i][0]) != findRoot(pipes[i][1]) ) {
                unite(pipes[i][0],pipes[i][1]);
                ans += pipes[i][2];
                --cc;
                if( cc == 1 ) break; // all houses are connected
            }
        }

       return ans;
    }
};
