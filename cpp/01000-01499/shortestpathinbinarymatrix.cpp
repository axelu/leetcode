
// 1091. Shortest Path in Binary Matrix
// https://leetcode.com/problems/shortest-path-in-binary-matrix/
// day 13 February challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3638/




class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if( grid[0][0] == 1 ) return -1;
        int N = grid.size(); // N by N square grid: N rows and N cols
        if( grid[N-1][N-1] == 1 ) return -1;

        // undirected graph
        int n = N*N;
        set<int> g[n];
        int u,v;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if( grid[i][j] == 1 ) continue; // blocked
                u = i*N+j;
                // look at all 8 adjacent cells and if there is a path,
                //     then add that edge and backedge (undirect graph)
                // north
                if( i > 0 && grid[i-1][j] == 0 ) {
                    v = (i-1)*N+j;
                    g[u].insert(v);
                    g[v].insert(u);
                }
                // north east
                if( i > 0 && j < N-1 && grid[i-1][j+1] == 0 ) {
                    v = (i-1)*N+(j+1);
                    g[u].insert(v);
                    g[v].insert(u);
                }
                // east
                if( j < N-1 && grid[i][j+1] == 0 ) {
                    v = i*N+(j+1);
                    g[u].insert(v);
                    g[v].insert(u);
                }
                // south east
                if( i < N-1 && j < N-1 && grid[i+1][j+1] == 0 ) {
                    v = (i+1)*N+(j+1);
                    g[u].insert(v);
                    g[v].insert(u);
                }
                // south
                if( i < N-1 && grid[i+1][j] == 0 ) {
                    v = (i+1)*N+j;
                    g[u].insert(v);
                    g[v].insert(u);
                }
                // south west
                 if( i < N-1 && j > 0 && grid[i+1][j-1] == 0 ) {
                    v = (i+1)*N+(j-1);
                    g[u].insert(v);
                    g[v].insert(u);
                }
                // west
                if( j > 0 && grid[i][j-1] == 0 ) {
                    v = i*N+(j-1);
                    g[u].insert(v);
                    g[v].insert(u);
                }
                // north west
                if( i > 0 && j > 0 && grid[i-1][j-1] == 0 ) {
                    v = (i-1)*N+(j-1);
                    g[u].insert(v);
                    g[v].insert(u);
                }
            }
        }

        // BFS
        int seen[n]; memset(seen,0,sizeof seen);
        int added[n]; memset(added,0,sizeof added);
        queue<pair<int,int>> q;
        q.push({0,1});
        int depth;
        while( !q.empty() ) {
            u = q.front().first;
            depth = q.front().second;
            q.pop();
            if( u == n-1 )
                return depth;
            seen[u] = 1;
            for(auto it = g[u].rbegin(); it != g[u].rend(); ++it) {
                v = *it;
                if( !seen[v] && !added[v] ) {
                    q.push({v,depth+1});
                    added[v] = 1;
                }
            }
        }
        return -1;
    }
};
