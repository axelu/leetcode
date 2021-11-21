
// 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
// https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/





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

    int buildMinimumSpanningTree(int n, vector<vector<int>>& edgeList,
                                 int edgeToSkip, int edgeToInclude,
                                 vector<int>& acceptedEdgeList) {
        int i;
        // weighted undirected connected graph
        // n vertices numbered from 0 to n-1

        // minimum spanning tree (Kruskal's algorithm)
        // edges[i] = [u,v,weight]
        // edges are sorted by weight of edges ascending aka lowest weight edge first

        int _parent[n]; parent = _parent;
        for(i = 0; i < n; ++i)
            parent[i] = i; // initially each node is connected to itself only

        // as our edgeList is sorted by cost and starts with the cheapest edge, our graph
        // will only include the cheapest edges that connect two vertices.
        int weight = 0;    // weight of minimum spanning tree

        if( edgeToInclude != -1 ) {
            acceptedEdgeList.push_back(edgeToInclude);
            unite(edgeList[edgeToInclude][0],edgeList[edgeToInclude][1]);
            weight += edgeList[edgeToInclude][2];
            --n;
        }

        for(i = 0; i < edgeList.size(); ++i) {
            if( i == edgeToSkip )
                continue;

            if( findRoot(edgeList[i][0]) != findRoot(edgeList[i][1]) ) {
                acceptedEdgeList.push_back(i);
                unite(edgeList[i][0],edgeList[i][1]);
                weight += edgeList[i][2];
                if( --n == 1 ) // all vertices are connected
                    break;
            }
        }
        return n == 1 ? weight : 100001;
    }

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int i;

        // weighted undirected connected graph
        // n vertices numbered from 0 to n-1

        // minimum spanning tree (Kruskal's algorithm)

        // edges[i]    = [u,v,weight]
        // edgeList[i] = [u,v,weight,index];
        // edges to edgeList
        vector<vector<int>> edgeList(edges.size(),vector<int>(4));
        for(i = 0; i < edges.size(); ++i)
            edgeList[i] = {edges[i][0],edges[i][1],edges[i][2],i};



        // sort edgeList by weight of edges ascending aka lowest weight edge first
        sort(edgeList.begin(),edgeList.end(),[](const vector<int>& a, const vector<int>& b){
           return  a[2]<b[2];
        });

        vector<int> acceptedEdgeList;
        unordered_set<int> criticalEdges;
        unordered_set<int> pseudoCriticalEdges;


        // build the best possible minimum spanning tree
        int min_weight = buildMinimumSpanningTree(n,edgeList,-1,-1,acceptedEdgeList);
        for(int e : acceptedEdgeList)
            pseudoCriticalEdges.insert(e);


        int weight;
        for(i = 0; i < edges.size(); ++i) {
            acceptedEdgeList.clear();
            weight = buildMinimumSpanningTree(n,edgeList,i,-1,acceptedEdgeList);
            if( weight > min_weight ) {
                criticalEdges.insert(i);
            } else if( weight == min_weight ) {
                for(int e : acceptedEdgeList)
                    pseudoCriticalEdges.insert(e);
            }
        }

        // are there edges that have not been used at all?
        // if so, force their usage
        for(i = 0; i < edges.size(); ++i) {
            if( !pseudoCriticalEdges.count(i) ) {
                acceptedEdgeList.clear();
                weight = buildMinimumSpanningTree(n,edgeList,i,i,acceptedEdgeList);
                if( weight == min_weight )
                    pseudoCriticalEdges.insert(i);
            }
        }


        vector<vector<int>> ans(2);

        for(int e : criticalEdges)
            ans[0].push_back(edgeList[e][3]);

        for(int e : pseudoCriticalEdges) {
            if( !criticalEdges.count(e) )
                ans[1].push_back(edgeList[e][3]);
        }

        return ans;
    }
};
