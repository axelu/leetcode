
// 1568. Minimum Number of Days to Disconnect Island
// https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/





// https://www.redblobgames.com/pathfinding/grids/graphs.html

// see also https://leetcode.com/problems/critical-connections-in-a-network/
// https://www.thealgorists.com/Algo/GraphTheory/Tarjan/Bridges
// Finding Bridges in a Connected Undirected Graph using Tarjan's Algorithm

// https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs

class Solution {
private:
    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    int id;

    void explore(vector<vector<int>>& grid, int m, int n, int i, int j, int seen[],
                 vector<int> g[]) {

        // cout << "i " << i << " j " << j << " id " << id << endl;

        int localId = id++;
        int seenIdx = i*n+j;
        seen[seenIdx] = localId;

        int i_new,j_new;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new == m ) {
                continue;
            }
            j_new = j+dirC[k];
            if( j_new < 0 || j_new == n ) {
                continue;
            }

            // water?
            if( !grid[i_new][j_new] )
                continue;

            // land we have seen before?
            if( seen[i_new*n+j_new] != -1 ) {
                g[localId].push_back(seen[i_new*n+j_new]);
                continue;
            }

            g[localId].push_back(id);
            explore(grid,m,n,i_new,j_new,seen,g);
        }
    }

    bool dfs(vector<int> g[], int seen[],
             int u, int discoveryTimes[], int low[], int parent[], int& discoveryTime) {

        seen[u] = 1;
        ++discoveryTime;  // increment discovery time before assigning
        discoveryTimes[u] = discoveryTime;
        low[u] = discoveryTime;

        int v; // adjacent node
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i];

            if( !seen[v]) {
                // the adjacent node is NOT an ancestor
                parent[v] = u;
                if( dfs(g,seen,v,discoveryTimes,low,parent,discoveryTime) )
                    return true;
                low[u] = min(low[u],low[v]);
            } else {
                // the adjacent node is an ancestor
                if( parent[u] != v) {
                    // the adjacent node is NOT the parent
                    low[u] = min(low[u],discoveryTimes[v]);
                }
            }
            if( low[v] > discoveryTimes[u]) {
                return true; // bridge found
            }
        }
        return false;
    }

public:
    int minDays(vector<vector<int>>& grid) {
        // - if the grid has 0 or 1+ islands -> 0 days
        // - if the island has a land cell with 3 or more sites of water -> 1 day
        // - if the island has a CRITICAL bridge -> 1 day
        // otherwise the answer is 2 days
        // a bridge is a land cell where oposite sites have water and
        //   the other oposite sites have land OR
        // where two adjacent sides have land and the enclosing diagonal has no land
        // a bridge is CRITICAL if destroying it would create two disconnected islands
        // outside the grid is considered water
        // edge cases: island with 2 cells will always take 2 days
        //             island with 1 or 3 cells will always take only 1 day

        int m = grid.size();
        int n = grid[0].size();

        int seen[m*n];
        for(int i = 0; i < m*n; ++i)
            seen[i] = -1;

        id = 0;
        vector<int> g[m*n]; // undirected graph

        int cnt = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] && seen[i*n+j] == -1 ) { // land not seen before
                    if( cnt == 1 ) return 0;            // more than one island
                    ++cnt;
                    explore(grid,m,n,i,j,seen,g);
                }
            }
        }
        if( cnt == 0 ) return 0; // no island
        if( id == 1 )  return 1; // 1 cell island
        if( id == 2 )  return 2; // 2 cell island
        if( id == 3 )  return 1; // 3 cell island


        // is there a CRITICAL bridge/connection in our graph?
        int discoveryTimes[id];
        int low[id]; // earliest discovered node reachable from node at idx
                    //     by not using backedge that goes through parent
        int parent[id];
        memset(seen,0,sizeof seen);

        /*
        // debug
        for(int i = 0; i < id; ++i) {
            cout << "id " << i << ": ";
            for(int j = 0; j < g[i].size(); ++j)
                cout << g[i][j] << " ";
            cout << endl;

        }
        */

        int discoveryTime = -1;
        return dfs(g,seen,0,discoveryTimes,low,parent,discoveryTime) ? 1 : 2;
    }
};
