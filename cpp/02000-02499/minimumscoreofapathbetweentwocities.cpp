
// 2492. Minimum Score of a Path Between Two Cities
// https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/



class Solution {
private:
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

public:
    int minScore(int n, vector<vector<int>>& roads) {
        // idea
        //     create the connected components
        //     sort roads by distance
        //     the constraints state: There is at least one path between 1 and n.
        //     in other words: city 1 and n are part of the same connected component
        //     so if we iterate through road by distance ascending and check if
        //       the cities it connects (checking one city is sufficient) are in the same component
        //       then that is our answer

        // union find

        int _parent[n+1];parent = _parent;
        for(int i = 0; i <= n; ++i)
            _parent[i] = i; // initially each node is connected to itself

        for(auto& v: roads)
            unite(v[0],v[1]);

        sort(roads.begin(),roads.end(),[](const vector<int>& a, const vector<int>& b){
            return a[2] < b[2];
        });

        int cc = findRoot(1); // equivalent to findRoot(n);

        for(auto& v: roads)
            if( findRoot(v[0]) == cc ) // equivalent to findRoot(v[1]) == cc
                return v[2];

        return -1; // satisfy compiler, should never reach here based on constraints
    }
};
