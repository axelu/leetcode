
// 3123. Find Edges in Shortest Paths
// https://leetcode.com/problems/find-edges-in-shortest-paths/





class Solution {
private:
    // Dijkstra's algorithm
    void shortestPath(vector<vector<int>> G[], long A[]) {

        // min heap
        auto cmp = [](const pair<long,int>& a, const pair<long,int>& b) {
            return a.first > b.first;
        };
        priority_queue<pair<long,int>,vector<pair<long,int>>,decltype(cmp)> pq(cmp);

        // push our source vertex into priority queue
        pq.push({0L,0});
        // set distance to our source vertex itself to 0
        A[0] = 0L;

        int u,v;
        long weight;
        while(!pq.empty()) {

            u = pq.top().second;
            pq.pop();

            vector<vector<int>>::iterator it;
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

        return;
    }

    vector<bool> ans;

    bool dfs(vector<vector<int>> G[], int n, int u, long d, long A[]) {
            if( u == n-1 )
                return true;

            bool ret = false;

            int v, edge_idx;
            long weight;
            vector<vector<int>>::iterator it;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                v = (*it)[0];
                weight = (*it)[1];
                edge_idx = (*it)[2];

                if( d + weight > A[v] )
                    continue;

                bool f = dfs(G, n, v, d + weight, A);
                if( f ) {
                    ans[edge_idx] = true;
                    ret = true;
                }
            }

        return ret;
    }

public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {

        vector<vector<int>> G[n]; // undirected weighted graph
        int e_sz = edges.size();
        for(int i = 0; i < e_sz; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            int weight = edges[i][2];
            G[u].push_back({v,weight,i});
            G[v].push_back({u,weight,i});
        }

        // distances
        long A[n];
        for(int i = 0; i < n; ++i)
            A[i] = 5000000001;

        shortestPath(G, A);

        ans.assign(e_sz,false);

        dfs(G, n, 0, 0L, A);

        return ans;
    }
};
