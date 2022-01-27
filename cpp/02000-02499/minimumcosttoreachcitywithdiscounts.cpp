
// 2093. Minimum Cost to Reach City With Discounts
// https://leetcode.com/problems/minimum-cost-to-reach-city-with-discounts/



class Solution {
private:
    // Dijkstra's algorithm
    int shortestPath(int n, vector<array<int,2>> G[], int s, int d, int discounts) {

        // min heap
        priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;

        // distances discounts left
        int A[n+1][discounts+1];
        for(int i = 0; i < n+1; ++i)
            for(int j = 0; j < discounts+1; ++j)
                A[i][j] = 1000000000;

        // push our source vertex into priority queue
        pq.push({0,s,discounts}); // distance,source,discounts
        // set distance to our source vertex itself to 0
        for(int j = 0; j < discounts+1; ++j)
            A[s][j] = 0;

        int u,v,k,weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            if( u == d )
                break;
            k = pq.top()[2];
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];

                // if we have discounts left, we have a choice
                // to apply a discount or not

                //  If there is shorter path to v through u.
                if( A[v][k] > A[u][k] + weight ) {
                    // Updating distance of v
                    A[v][k] = A[u][k] + weight;
                    pq.push({A[v][k],v,k});
                }

                // apply a discount
                if( k > 0 ) {
                    int t = weight / 2;
                    if( A[v][k-1] > A[u][k] + t ) {
                        // Updating distance of v
                        A[v][k-1] = A[u][k] + t;
                        pq.push({A[v][k-1],v,k-1});
                    }
                }

            }
        }

        int mn = 1000000000;
        for(int j = 0; j < discounts+1; ++j)
            mn = min(mn,A[d][j]);
        return mn;
    }

public:
    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {

        // undirected weighted graph
        vector<array<int,2>> G[n];
        int u,v,weight;
        for(auto& h : highways) {
            u = h[0];
            v = h[1];
            weight = h[2];
            G[u].push_back({v,weight});
            G[v].push_back({u,weight});
        }

        int t = shortestPath(n,G,0,n-1,discounts);
        return t == 1000000000 ? -1 : t;
    }
};
