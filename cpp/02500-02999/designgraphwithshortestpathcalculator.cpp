
// 2642. Design Graph With Shortest Path Calculator
// https://leetcode.com/problems/design-graph-with-shortest-path-calculator/

// inspired by
// https://stackoverflow.com/questions/47810442/maintain-shortest-paths-while-updating-graph




class Graph {
private:
    int n;
    int dist[100][100];
public:
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;

        // directed weighted graph
        // n nodes numbered from 0 to n-1
        // edges[i] = [u,v,weight] represents a directional and weighted edge between nodes

        int i,j,k;
        long u,v,w;

        // Floyd-Warshall
        // compute any-point to any-point distances
        // initialize distances
        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j)
                dist[i][j] = 100000001; // max 100 nodes, max edgecost 1000000 -> 100 * 1000000 = 100000000 worst case

        for(i = 0; i < edges.size(); ++i) {
            u = edges[i][0];
            v = edges[i][1];
            w = edges[i][2];
            dist[u][v] = w;
        }

        for(i = 0; i < n; ++i)
            dist[i][i] = 0;

        for(k = 0; k < n; ++k)
            for(i = 0; i < n; ++i)
                for(j = 0; j < n; ++j)
                    if( dist[i][j] > dist[i][k] + dist[k][j] )
                        dist[i][j] = dist[i][k] + dist[k][j];

    }

    void addEdge(vector<int> edge) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];

        // if the new edge is equal or greater than an
        // existing path between the two nodes, then we
        // will NOT even add this edge
        if( dist[u][v] <= w )
            return;

        dist[u][v] = w;

        // we need to update the shortest path matrix
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                // dist between i and j using the new edge
                int t = dist[i][u] + dist[u][v] + dist[v][j];

                if( dist[i][j] > t )
                    dist[i][j] = t;
            }
    }

    int shortestPath(int node1, int node2) {
        return dist[node1][node2] != 100000001 ? dist[node1][node2] : -1;
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
