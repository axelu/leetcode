
// 3620. Network Recovery Pathways
// https://leetcode.com/problems/network-recovery-pathways/





class Solution {
private:
    int n;

    // Dijkstra's algorithm
    long long A[50000];
    void shortestPath(vector<vector<int>>& edges, vector<bool>& online, long long k) {

        vector<pair<int, long long>> G[50000]; // cost, node

        for(auto& edge: edges) {
            int u = edge[0];
            if( !online[u] )
                continue;

            int v = edge[1];
            if( !online[v] )
                continue;

            long long cost = edge[2];
            if( cost > k )
                continue;

            // reverse direction !!!
            G[v].push_back({u, cost});
        }

        // min heap
        auto cmp = [](const pair<long long, int>& a, const pair<long long, int>& b){
            return a.first > b.first;
        };
        priority_queue<pair<long long,int>,vector<pair<long long,int>>,decltype(cmp)> pq(cmp);

        // distances
        for(int i = 0; i < n; ++i)
            A[i] = 50000000000001;

        // push our source vertex into priority queue
        pq.push({0,n-1});
        // set distance to our source vertex itself to 0
        A[n-1] = 0LL;

        int u,v;
        long long weight;
        while( !pq.empty() ) {

            u = pq.top().second;
            pq.pop();

            vector<pair<int,long long>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it).first;
                weight = (*it).second;

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        return;
    }

    vector<pair<int,int>> g[50000];

    bool dfs(int u, long long k, int limit) {
        if( u == n-1 )
            return true;

        // only use edges with cost >= limit

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i].first;
            int cost = g[u][i].second;

            if( cost < limit )
                continue;
            long long k_new = k - (long long)cost;
            if( k_new < 0LL )
                continue;
            // can we still make it?
            if( k_new < A[v] )
                continue;

            if( dfs(v, k_new, limit) )
                return true;
        }

        return false;
    }

    // binary search
    int search(const long long k, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( dfs(0, k, mid) ) {
            // can we do better?
            int t = search(k, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(k, s, mid-1);
    }


public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        n = online.size();

        // directed acyclic graph of n nodes numbered from 0 to n − 1

        shortestPath(edges, online, k);
        if( A[0] == 50000000000001 ) // there is no path from 0 to n-1 with a budget of k
            return -1;

        int mn_cost = 1e9;
        int mx_cost = 0;

        for(auto& edge: edges) {
            int u = edge[0];
            if( !online[u] )
                continue;

            int v = edge[1];
            if( !online[v] )
                continue;

            int cost = edge[2];
            if( (long long)cost > k )
                continue;

            mn_cost = min(mn_cost, cost);
            mx_cost = max(mx_cost, cost);

            g[u].push_back({v, cost});
        }

        // binary search
        // we only use edges greater equal a target
        return search(k, mn_cost, mx_cost);
    }
};
