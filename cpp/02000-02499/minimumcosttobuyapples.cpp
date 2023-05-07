
// 2473. Minimum Cost to Buy Apples
// https://leetcode.com/problems/minimum-cost-to-buy-apples/



class Solution {
private:

    // Dijkstra's algorithm
    vector<int> shortestPath(int n, vector<array<int,2>> G[], int s) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        vector<int> A(n,INT_MAX);

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

        return A;
    }

public:
    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {

        vector<array<int,2>> G[n]; // bidirectional graph

        // cities in roads are 1-indexed, so changing to 0 indexed
        for(auto& v: roads) {
            G[v[0]-1].push_back({v[1]-1,v[2]});
            G[v[1]-1].push_back({v[0]-1,v[2]});
        }

        vector<long long> ans(n);
        for(int i = 0; i < n; ++i) {

            vector<int> A = shortestPath(n,G,i);
            long long t = LLONG_MAX;

            for(int j = 0; j < n; ++j) {
                long long c = (long)A[j] + (long)k * A[j] + (long)appleCost[j];
                t = min(t,c);
            }
            ans[i] = t;
        }

        return ans;
    }
};
