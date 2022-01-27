
// 990. Satisfiability of Equality Equations
// https://leetcode.com/problems/satisfiability-of-equality-equations/





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
    bool equationsPossible(vector<string>& equations) {
        // we will assume each equality equation as an edge
        // and unite the nodes

        int n = 26, i;

        int _parent[n]; parent = _parent;
        for(i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only


        // pass 1
        // unite all equality equations
        for(i = 0; i < equations.size(); ++i)
            if( equations[i][1] == '=' ) {
                if( equations[i][0] == equations[i][3] )
                    continue;
                if( findRoot(equations[i][0]-'a') != findRoot(equations[i][3]-'a') )
                   unite(equations[i][0]-'a',equations[i][3]-'a');
            }

        // pass 2
        // check all inequality equations
        for(i = 0; i < equations.size(); ++i)
            if( equations[i][1] == '!' ) {
                if( equations[i][0] == equations[i][3] )
                    return false;
                if( findRoot(equations[i][0]-'a') == findRoot(equations[i][3]-'a') )
                    return false;
            }

        return true;
    }
};
