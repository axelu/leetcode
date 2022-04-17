
// 1976. Number of Ways to Arrive at Destination
// https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/




class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {

        long mod = 1000000007;

        // undirected weighted graph
        vector<array<int,2>> G[n];
        for(int i = 0; i < roads.size(); ++i) {
            G[roads[i][0]].push_back({roads[i][1],roads[i][2]});
            G[roads[i][1]].push_back({roads[i][0],roads[i][2]});
        }

        // Dijkstra's algorithm

        // min heap
        priority_queue<array<long,2>,vector<array<long,2>>,greater<array<long,2>>> pq;

        // distances
        long A[n];
        for(int i = 0; i < n; ++i)
            A[i] = LONG_MAX;

        // push our source vertex into priority queue
        // our source vertex is 0
        pq.push({0L,0L}); // distance,vertex
        // set distance to our source vertex itself to 0
        A[0] = 0L;

        long cnt[n]; // count of possible paths to get to given vertex
        for(int i = 0; i < n; ++i)
            cnt[i] = 0L;
        cnt[0] = 1L; // our source vertex is 0, so we have 1 way to get to it

        long u,d,v,weight;
        while(!pq.empty()) {

            d = pq.top()[0]; // distance it took us to get to u
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

                    // there are as many path to get to v
                    // as there are to get to u
                    cnt[v] = cnt[u];

                } else if( A[v] == d + weight ) {
                    // if the distance it took us to get to u plus
                    // the distance it takes us to get from u to v
                    // is equal the shortest distance already recorded to v
                    // then we can get to v also using all the paths to got to u
                    cnt[v] = (cnt[v] + cnt[u]) % mod;
                }
            }
        }

        return cnt[n-1]; // count of paths to destination vertex
    }
};
