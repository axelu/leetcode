
// 1786. Number of Restricted Paths From First to Last Node
// https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/





class Solution {
private:
    // Dijkstra's algorithm
    void shortestPath(int n, vector<array<int,2>> G[], int s, int A[]) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

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
    }

    long MOD = 1000000007;

    long dfs(vector<int> G[], int u, int target, long seen[]) {
        if( u == target ) {
            // cout << "reached target" << endl;
            return 1;
        }

        if( seen[u] != -1L ) {
            return seen[u];
        }

        long ret = 0;
        int v;
        for(int i = 0; i < G[u].size(); ++i) {
            v = G[u][i];
            ret = (ret + dfs(G,v,target,seen)) % MOD;
        }

        return seen[u] = ret;
    }

public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        // n nodes numbered from 1 to n
        int i;

        // undirected weigthed connected graph
        vector<array<int,2>> g1[n+1];
        for(i = 0; i < edges.size(); ++i) {
            g1[edges[i][0]].push_back({edges[i][1],edges[i][2]});
            g1[edges[i][1]].push_back({edges[i][0],edges[i][2]});
        }

        // distances
        int A[n+1];
        for(i = 1; i < n+1; ++i)
            A[i] = INT_MAX;

        shortestPath(n,g1,n,A);

        // directed acyclic graph (DAG)
        vector<int> g2[n+1];
        int u,v;
        for(i = 0; i < edges.size(); ++i) {
            u = edges[i][0];
            v = edges[i][1];
            if( A[u] == A[v] ) {
                continue;
            } else if( A[u] > A[v] ) {
                // cout << "g2 adding edge u " << u << " v " << v << endl;
                g2[u].push_back(v);
            } else {
                // cout << "g2 adding edge u " << v << " v " << u << endl;
                g2[v].push_back(u);
            }
        }

        // DFS
        long seen[n+1];
        for(i = 0; i <=n; ++i)
            seen[i] = -1L;


        return dfs(g2,1,n,seen);
    }
};
