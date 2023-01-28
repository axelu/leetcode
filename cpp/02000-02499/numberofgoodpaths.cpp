
// 2421. Number of Good Paths
// https://leetcode.com/problems/number-of-good-paths/




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
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();

        int _parent[n]; parent = _parent;
        for(int i = 0; i < n; ++i)
            parent[i] = i;  // initially each node is connected to itself only

        vector<int> g[n]; // bi-directional connected graph
        for(auto& v: edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        // map of node value to nodes having same value
        map<int,vector<int>> value_to_nodes;
        for(int i = 0; i < n; ++i)
            value_to_nodes[vals[i]].push_back(i);

        int ans = 0;

        // our constraints are that
        //    starting node and the ending node have the same value
        //    nodes between the starting node and the ending node have values less than or equal to the starting node
        // so we start with nodes with the lowest value and only traverse from a node 'u' to a Node 'v'
        // if vals[u] >= vals[v], we unite u and v and with that create or extend connected components (cc).
        // if we then count the nodes with the current value in each component we created or extended, we can then
        // calculate the number of paths between the nodes with said value and add to our answer
        for(auto& [_,nodes]: value_to_nodes) {

            for(int u: nodes)
                for(int v: g[u])
                    if( vals[u] >= vals[v] )
                        unite(u,v);

            // we now need to find out how many nodes with the current value
            // are part of the component that we added them to
            unordered_map<int,int> ccvaluecount;
            for(int u: nodes) {
                int root = findRoot(u);
                ccvaluecount[root]++;
            }

            for(auto& [_,count]: ccvaluecount)
                    ans += (count * (count + 1)/2);
        }

        return ans;
    }
};
