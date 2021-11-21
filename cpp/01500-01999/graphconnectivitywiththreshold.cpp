
// 1627. Graph Connectivity With Threshold
// https://leetcode.com/problems/graph-connectivity-with-threshold/




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
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        int m = queries.size();
        if( threshold == 0 ) {
            vector<bool> ans(m,true);
            return ans;
        }

        // only cities with with label > threshold need to be considered
        // idea:
        //   create a map <divisor,list of cities> which basically tells us
        //   that those cities are connected
        //   threshold < divisor <= n
        //   each of those we unite and can then answer our queries

        int _parent[n+1]; parent = _parent;
        for(int i = 0; i < n+1; ++i)
            parent[i] = i;  // initially each node is connected to itself only

        // threshold == 0 -> all cities are connected, because 1 is a common divisor of all
        // worst case: n = 10000, threshold = 1
        for(int city = threshold+1; city <= n; ++city)
            for(int divisor = threshold+1; divisor <= city; ++divisor)
                if( city % divisor == 0 )
                    unite(divisor,city);

        vector<bool> ans(m,false);
        for(int i = 0,a,b; i < m; ++i) {
            a = queries[i][0];
            if( a <= threshold )
                continue;
            b = queries[i][1];
            if( b <= threshold )
                continue;

            if( findRoot(a) == findRoot(b) )
                ans[i] = true;
        }


        return ans;
    }
};
