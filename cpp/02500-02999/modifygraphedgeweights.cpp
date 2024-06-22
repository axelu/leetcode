
// 2699. Modify Graph Edge Weights
// https://leetcode.com/problems/modify-graph-edge-weights/






class Solution {
private:
    const int INF = 2000000000;

public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {

        // Floyd-Warshall
        // compute any-point to any-point distances
        long dist[n][n]; // minimum distances initialized to ∞ (infinity)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                dist[i][j] = (long)INF;

        for(auto& edge: edges) {
            long w = edge[2];
            if( w != -1L ) {
                int u = edge[0];
                int v = edge[1];
                dist[u][v] = w;
                dist[v][u] = w;
            }
        }

        for(int i = 0; i < n; ++i)
            dist[i][i] = 0L;

        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    if( dist[i][j] > dist[i][k] + dist[k][j] )
                        dist[i][j] = dist[i][k] + dist[k][j];

        if( dist[source][destination] < target )
            return {};
        if( dist[source][destination] == target ) {
            for(auto& edge: edges) {
                int& w = edge[2];
                if( w == -1 )
                    w = INF;
            }
            return edges;
        }

        // add modifiable edges
        bool f = false;
        for(auto& edge: edges) {
            int& w = edge[2];
            if( w == -1 ) {
                if( f ) {
                    w = (int)INF;
                    continue;
                }
                int u = edge[0];
                int v = edge[1];
                // cout << "at modifiable edge u " << u << " v " << v << endl;
                // add edge u -> v with distance of 1
                dist[u][v] = 1L;
                dist[v][u] = 1L;
                w = 1;

                // update i -> u -> v -> j, i -> v -> u -> j, whichever is smaller
                for(int i = 0; i < n; ++i) {
                    for(int j = 0; j < n; ++j) {
                        long t = min(dist[i][u] + 1L + dist[v][j], dist[i][v] + 1L + dist[u][j]);
                        if( dist[i][j] > t ) {
                            // cout << "  updating distance i " << i << " j " << j << " to " << t << endl;
                            dist[i][j] = t;
                            dist[j][i] = t;
                        }
                    }
                }
                if( dist[source][destination] <= target ) {
                    long t = min(dist[source][u] + dist[v][destination], dist[source][v] + dist[u][destination]);
                    dist[u][v] = (target - t);
                    dist[v][u] = (target - t);
                    w = (int)(target - t);
                    f = true;
                }
            }
        }
        if( !f )
            return {};

        return edges;
    }
};
