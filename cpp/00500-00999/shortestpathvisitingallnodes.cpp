
// 847. Shortest Path Visiting All Nodes
// https://leetcode.com/problems/shortest-path-visiting-all-nodes/




class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        // undirected connected graph of n nodes labeled from 0 to n - 1
        int n = graph.size(); // 1 <= n <= 12


        // Dijkstra's algorithm
        // shortest path adapted


        // distances[node][bitmask] stores the shortest path to get to node
        // after visiting some nodes.  The visited nodes are encoded in
        // the bitmask, e.g. if node 0 and 1 had been visited, the mask
        // would look like this for a graph with 12 nodes: 000000000011
        // initial length is infinity, except length to get started is zero
        map<array<int,2>,int> A; // key: node,bitmask


        // min heap based on weight, respectively distance
        auto cmp = [A] (const array<int,2>& a, const array<int,2>& b) mutable {
            return A[{a[0],a[1]}] > A[{b[0],b[1]}];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);


        // push our source vertex into priority queue with a distance of 0
        // we are starting from every vertex 0 to n-1
        // set distance to our source vertex itself to 0
        int mask;
        for(int i = 0; i < n; ++i) {
            mask = 0 ^ (1 << i); // set the ith bit = mark our source vertex as visited
            A[{i,mask}] = 0;
            pq.push({i,mask});
        }

        int u,v,mask_v;
        while(!pq.empty()) {

            u    = pq.top()[0];
            mask = pq.top()[1];
            pq.pop();

            // distance it took us to get here
            // A[{u,mask}];


            vector<int>::iterator it;
            for(it = graph[u].begin(); it != graph[u].end(); ++it) {
                v = *it;
                mask_v = 0 ^ (1 << v);

                // lazy insert
                if( !A.count({v,mask|mask_v}) )
                    A[{v,mask|mask_v}] = INT_MAX;

                //  If there is shorter path to v through u.
                if( A[{v,mask|mask_v}] > A[{u,mask}] + 1 ) { // each edge has lenght of 1
                    // Updating distance of v
                    A[{v,mask|mask_v}] = A[{u,mask}] + 1;
                    pq.push({v,mask|mask_v});
                }

            }
        }

        int ans = INT_MAX;
        mask = pow(2,n)-1; // mask when all nodes visted
        for(int i = 0; i < n; ++i) {
            // cout << "i:" << i << " " << A[{i,mask}] << " " << endl;
            ans = min(ans,A[{i,mask}]);
        }
        return ans;
    }
};
