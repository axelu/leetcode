
// 3650. Minimum Cost Path with Edge Reversals
// https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/




class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        // note: as one would not traverse a node twice
        // I don't see how we would ever return -1,
        // meaning not be able to reach node n-1,
        // unless node n-1 is not connected to node 0

        // why don't we record edges in their original
        // direction with w, and their opposite direction with 2*w
        // no need to track if we switch an edge or not

        // Dijkstra's algorithm shortest path

        vector<array<int,2>> G[50000]; // 2 <= n <= 5 * 1e4

        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            G[u].push_back({v,w});
            G[v].push_back({u,2*w});
        }

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[50000];
        for(int i = 0; i < n; ++i)
            A[i] = 1000000001;

        int s = 0; // source vertex

        // push our source vertex into priority queue
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        int d = n-1; // destination vertex
        return A[d] != 1000000001 ? A[d] : -1;
    }
};
