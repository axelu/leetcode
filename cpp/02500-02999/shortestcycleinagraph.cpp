
// 2608. Shortest Cycle in a Graph
// https://leetcode.com/problems/shortest-cycle-in-a-graph/




class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        // small constraint 2 <= n <= 1000

        vector<int> g[n]; // bi-directional graph
        for(auto& edge: edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        int ans = INT_MAX;

        for(int i = 0; i < n; ++i) {

            // BFS
            queue<array<int,3>> q; // u,src,step
            q.push({i,-1,0});
            bool seen[n][n];memset(seen,false,sizeof seen);
            while( !q.empty() ) {
                int step = q.front()[2];
                if( step + 1 == ans )
                    break;

                int u = q.front()[0];
                int src = q.front()[1];
                q.pop();

                bool done = false;
                for(int v: g[u]) {
                    if( v == src )
                        continue;

                    if( v == i ) {
                        ans = min(ans, step+1);
                        done = true;
                        break;
                    }

                    if( seen[v][u] )
                        continue;

                    seen[v][u] = true;
                    q.push({v,u,step+1});
                }
                if( done )
                    break;
            }

        }

        return ans != INT_MAX ? ans : -1;
    }
};
