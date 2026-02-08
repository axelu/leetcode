
// 3807. Minimum Cost to Repair Edges to Traverse a Graph
// https://leetcode.com/problems/minimum-cost-to-repair-edges-to-traverse-a-graph/




class Solution {
private:
    const long long INF = 50000000000000;

    // Dijkstra's algorithm
    long long shortestPath(int n, vector<array<int,2>> G[], long long weight_limit, int k) {
        // cout << "shortestPath weight_limit " << weight_limit << endl;
        // min heap {dist, steps, u}
        priority_queue<array<long long,3>,vector<array<long long,3>>,greater<array<long long,3>>> pq;

        // distances
        vector<long long> A(n, INF);
        // long long A[50000]; // n max = 50000
        // for(int i = 0; i < n; ++i) A[i] = INF;

        // push our source vertex into priority queue
        int s = 0; // source
        pq.push({0,0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v,steps;
        long long weight;
        while(!pq.empty()) {

            u = pq.top()[2];
            steps = pq.top()[1];
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (long long)(*it)[1];
                if( weight > weight_limit )
                    continue;

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    if( steps + 1 < k )
                        pq.push({A[v], steps + 1, v});
                }
            }
        }
        int d = n-1; // destination
        return A[d];
    }

    // Dijkstra's algorithm
    long long shortestPath(int n, vector<array<int,2>> G[]) {
        // min heap
        priority_queue<array<long long,2>,vector<array<long long,2>>,greater<array<long long,2>>> pq;

        // distances
        vector<long long> A(n, INF);
        // long long A[50000]; // n max = 50000
        // for(int i = 0; i < n; ++i) A[i] = INF;

        // push our source vertex into priority queue
        int s = 0; // source
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        int u,v;
        long long weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            vector<array<int,2>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = 1LL;

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }
        int d = n-1; // destination
        return A[d];
    }

    // binary search
    long long search(long long s, long long e, int n, vector<array<int,2>> G[], int k) {
        if( s > e )
            return -1;

        long long mid = s + ((e-s)/2LL);
        long long res = shortestPath(n, G, mid, k);
        if( res != INF ) {
            // can we do better?
            long long t = search(s, mid-1, n, G, k);
            return t != -1 ? t : mid;
        }
        return search(mid+1, e, n, G, k);
    }

public:
    int minCost(int n, vector<vector<int>>& edges, int k) {
        // 2 <= n <= 5 * 1e4
        // undirected graph with n nodes labeled from 0 to n-1
        // no self-loops or duplicate edges
        // edges[i] = [ui, vi, wi]
        // 1 <= edges.length == m <= 1e5
        // 1 <= wi <= 1e9
        // worst case
        //     50000 nodes aranged in a line 49999 edges with wi = 1e9 each
        //     we would need 49999 * 1e9 = 49999000000000 money
        //                  LLONG_MAX 9223372036854775807
        // if we do a Dijkstra with w = 1 for all edges we will know
        //     if we can even make it given k

        long long mn_w = LLONG_MAX;
        long long mx_w = LLONG_MIN;
        vector<array<int,2>> G[50000];
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            G[u].push_back({v, weight});
            G[v].push_back({u, weight});
            mn_w = min(mn_w, (long long)weight);
            mx_w = max(mx_w, (long long)weight);
        }

        // get min k
        long long k_mn = shortestPath(n, G); // cout << "k_mn " << k_mn << endl;
        if( k_mn > k )
            return -1;

        // long long tt1 = shortestPath(n, G, 99, k);
        // cout << "tt1 " << tt1 << endl;

        // so our answer is somewhere between hi: mx_w and lo: mn_w
        // cout << "mn_w " << mn_w << " mx_w " << mx_w << endl;
        return search(mn_w, mx_w, n, G, k);
    }
};
