
// 882. Reachable Nodes In Subdivided Graph
// https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/




class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        if( maxMoves == 0 )
            return 1;

        // n nodes labeled from 0 to n-1

        int i;

        // undirected weighted graph
        vector<array<int,2>> G[n];
        for(i = 0; i < edges.size(); ++i) {
            G[edges[i][0]].push_back({edges[i][1],edges[i][2]+1});
            G[edges[i][1]].push_back({edges[i][0],edges[i][2]+1});
        }


        // Dijkstra's algorithm
        // shortest path adapted

        // min heap based on weight, respectively distance
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;


        // distances;
        int A[n+1];
        for(int i = 0; i < n+1; ++i) A[i] = 1000000;


        // push our source vertex into priority queue with a distance of 0
        int s = 0; // we are starting from vertex 0
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int ans = 0;

        map<array<int,2>,int> used; // record how much of an edge we have used
                                    // directionally dependent

        int seen[n+1];memset(seen,0,sizeof seen); // don't double count nodes

        int u,v,weight,rem;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            // count u if the distance it took us to get here is
            // smaller than our maxMoves and we have not counted u before
            if( A[u] <= maxMoves && !seen[u] ) {
                ++ans;
                seen[u] = 1;
            }

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];

                // how much furter can we go?
                rem = maxMoves - A[u];

                // record how much of the edge u->v we can consume
                // at most it is the entire edge
                used[{u,v}] = max(used[{u,v}],min(weight,rem));


                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }

            }
        }

        // each edge can be used with a maximum
        // of weight, or from either side
        for(i = 0; i < edges.size(); ++i) {
            u      = edges[i][0];
            v      = edges[i][1];
            weight = edges[i][2];
            ans += min(weight,used[{u,v}]+used[{v,u}]);
        }

        return ans;
    }
};
