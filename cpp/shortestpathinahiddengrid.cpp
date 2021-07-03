
// 1778. Shortest Path in a Hidden Grid
// https://leetcode.com/problems/shortest-path-in-a-hidden-grid/




/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
 *     boolean isTarget();
 * };
 */

class Solution {
private:
    int m,n;

    // directions    R   D   L   U
    int dirR[4]  = { 0,  1,  0, -1};
    int dirC[4]  = { 1,  0, -1,  0};
    char dirG[4] = {'R','D','L','U'};

    // grid to graph DFS
    int explore(GridMaster& master, int u, int grid[]) {
        grid[u] = 1;
        // cout << "explore i u " << u << endl;

        int ret = master.isTarget() ? u : -1;
        if( ret != -1 ) return u;
        int t,i_new,j_new,v;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            if( !master.canMove(dirG[k]) )
                continue;

            i_new = u/n+dirR[k];
            j_new = u%n+dirC[k];

            v = i_new*n+j_new;

            // cell we have seen before?
            if( !grid[v] ) {
                master.move(dirG[k]);
                t = explore(master,v,grid);
                if( t != -1 ) ret = t;
                // back track
                if( k == 3 ) master.move('D');
                if( k == 1 ) master.move('U');
                if( k == 2 ) master.move('R');
                if( k == 0 ) master.move('L');
            }

        }
        return ret;
    }

public:
    int findShortestPath(GridMaster &master) {
        m = 999;
        n = 999;

        int N = m*n;

        int grid[N];memset(grid,0,sizeof grid);
        int seen[N];memset(seen,0,sizeof seen);

        // we start the robot at [499,499]
        int i = 499, j = 499;
        int s = i*n+j;                  // source
        int d = explore(master,s,grid); // destination
        if( d == -1 ) return -1;

        // BFS
        queue<array<int,2>> q;
        q.push({s,0});
        int u,v,step,i_new,j_new;
        while(!q.empty()) {
            u    = q.front()[0];
            step = q.front()[1];
            q.pop();
            // explore all 4 directions
            for(int k = 0; k < 4; ++k) {

                i_new = u/n+dirR[k];
                if( i_new < 0 || i_new >= m )
                    continue;

                j_new = u%n+dirC[k];
                if( j_new < 0 || j_new >= n )
                    continue;

                v = i_new*n+j_new;

                // did we arrive at the destination?
                if( v == d )
                    return step+1;

                // is it a path?
                if( !grid[v] )
                    continue;

                // have we seen this cell before?
                if( seen[v] )
                    continue;

                seen[v] = 1;
                q.push({v,step+1});
            }
        }
        return -1;
    }
};
