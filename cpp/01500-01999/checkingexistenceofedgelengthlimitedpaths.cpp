
// 1697. Checking Existence of Edge Length Limited Paths
// https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/






// could just copy solution to 1724. Checking Existence of Edge Length Limited Paths II
// https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths-ii/
// but while it passed, it was slow, hence here trying to implement minimum spanning tree (Kruskal's algorithm)

// see also 1102. Path With Maximum Minimum Value
// https://leetcode.com/problems/path-with-maximum-minimum-value/


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
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {

        int i;

        int _parent[n]; parent = _parent;
        for(i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        // edgeList[i] = [ui, vi, disi]
        // sort edgeList by length of edges ascending aka shortest edge first
        sort(edgeList.begin(),edgeList.end(),[](const vector<int>& a, const vector<int>& b){
           return  a[2]<b[2];
        });

        vector<vector<int>> g[n]; // undirected graph g[i] = [ui,disti]

        // queries[j] = [pj, qj, limitj]

        // sorting our queries by dist ascending
        auto cmp = [](vector<int>& a, const vector<int>& b) { return a[2]>b[2]; };
        priority_queue<vector<int>,vector<vector<int>>, decltype(cmp)> pq(cmp);
        for(i = 0; i < queries.size(); ++i) pq.push({queries[i][0],queries[i][1],queries[i][2],i});


        int j,p,q,limit;
        vector<bool> ans(queries.size(),false);
        i = 0;
        while(!pq.empty()) {
            p     = pq.top()[0];
            q     = pq.top()[1];
            limit = pq.top()[2];
            j     = pq.top()[3];
            pq.pop();

            // we will only edges to our graph if the edge distance is less than our current query limit
            // and the edge connects two vertices that are not yet connected;
            // as our edgeList is sorted by distance and starts with the shortest edge, our graph will only
            // included the shortest edges that connect two vertices.
            for(; i < edgeList.size(); ++i) {
                if( edgeList[i][2] >= limit ) break;
                if( findRoot(edgeList[i][0]) != findRoot(edgeList[i][1]) ) {
                    unite(edgeList[i][0],edgeList[i][1]);
                    g[edgeList[i][0]].push_back({edgeList[i][1],edgeList[i][2]});
                    g[edgeList[i][1]].push_back({edgeList[i][0],edgeList[i][2]});
                }
            }

            if( findRoot(p) == findRoot(q) ) ans[j] = true;


        } // queries end

        return ans;
    }
};
