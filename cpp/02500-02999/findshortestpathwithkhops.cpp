
// 2714. Find Shortest Path with K Hops
// https://leetcode.com/problems/find-shortest-path-with-k-hops/




class Solution {
public:
    int shortestPathWithHops(int n, vector<vector<int>>& edges, int s, int d, int k) {

        vector<array<int,2>> G[n]; // undirected weighted graph
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            G[u].push_back({v,weight});
            G[v].push_back({u,weight});
        }

        // Dijkstra's algorithm
        auto cmp = [](const array<int,3>& a, const array<int,3>& b){
            return a[0] > b[0];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);

        // distances
        int A[n][k+1];
        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= k; ++j)
                A[i][j] = INT_MAX;

        // push our source vertex into priority queue
        pq.push({0,s,0});
        // set distance to our source vertex itself to 0
        A[s][0] = 0;

        int u,v,h,weight;
        while( !pq.empty() ) {

            u = pq.top()[1];
            h = pq.top()[2]; // number of hops we consumed
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];

                //  Don't use a hop
                //  If there is shorter path to v through u.
                if( A[v][h] > A[u][h] + weight ) {
                    // Updating distance of v
                    A[v][h] = A[u][h] + weight;
                    pq.push({A[v][h], v, h});
                }

                // Use a hop if we have one left
                if( h < k )
                    if( A[v][h+1] > A[u][h] ) {
                        // Updating distance of v
                        A[v][h+1] = A[u][h];
                        pq.push({A[v][h+1], v, h+1});
                    }
            }
        }

        int mn = INT_MAX;
        for(int i = 0; i <= k; ++i)
            mn = min(mn,A[d][i]);

        return mn;

