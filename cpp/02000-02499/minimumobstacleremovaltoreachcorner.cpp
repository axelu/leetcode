
// 2290. Minimum Obstacle Removal to Reach Corner
// https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/




class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int g_sz = m*n;
        vector<array<int,2>> g[g_sz]; // directed graph
        int idx;
        //  directions R  D  L  U
        int dirR[] = { 0, 1, 0,-1};
        int dirC[] = { 1, 0,-1, 0};
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                int u = i * n + j;

                // explore all four directions
                for(int k = 0; k < 4; ++k) {
                    int i_new = i + dirR[k];
                    if( i_new < 0 || i_new == m )
                        continue;

                    int j_new = j + dirC[k];
                    if( j_new < 0 || j_new == n )
                        continue;

                    int v = i_new * n + j_new;
                    int weight = grid[i_new][j_new] == 1 ? 1 : 0;

                    g[u].push_back({v,weight});
                }
            }

        // BFS
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            return a[0] > b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        pq.push({0,0});
        int seen[g_sz];memset(seen,0,sizeof seen);
        int dest = g_sz-1;
        while( !pq.empty() ) {
            int pushes = pq.top()[0];
            int u = pq.top()[1];
            pq.pop();

            if( u == dest )
                return pushes;

            for(int k = 0; k < g[u].size(); ++k) {
                int v = g[u][k][0];
                int weight = g[u][k][1];

                if( !seen[v] ) {
                    pq.push({pushes+weight,v});
                    seen[v] = 1;
                }
            }
        }

        return -1; // satisfy compiler
    }
};
