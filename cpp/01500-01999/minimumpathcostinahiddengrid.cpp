
// 1810. Minimum Path Cost in a Hidden Grid
// https://leetcode.com/problems/minimum-path-cost-in-a-hidden-grid/




/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     int move(char direction);
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

    // grid to graph
    int explore(GridMaster& master, int i, int j, int seen[], vector<array<int,2>> G[]) {
        int u = i*n+j;
        seen[u] = 1;

        int ret = master.isTarget() ? u : -1;
        int t;
        int i_new,j_new,v,cost;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            if( !master.canMove(dirG[k]) )
                continue;

            i_new = i+dirR[k];
            j_new = j+dirC[k];

            v = i_new*n+j_new;
            cost = master.move(dirG[k]);
            G[u].push_back({v,cost});

            // cell we have seen before?
            if( !seen[v] ) {
                t = explore(master,i_new,j_new,seen,G);
                if( t != -1 ) ret = t;
            }

            // back track
            if( dirG[k] == 'U' ) master.move('D');
            if( dirG[k] == 'D' ) master.move('U');
            if( dirG[k] == 'L' ) master.move('R');
            if( dirG[k] == 'R' ) master.move('L');
        }
        return ret;
    }


    // Dijkstra's algorithm
    int shortestPath(int n, vector<array<int,2>> G[], int s, int d) {

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[n+1];
        for(int i = 0; i < n+1; ++i) A[i] = 1000000;

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

        return A[d];
    }


public:
    int findShortestPath(GridMaster &master) {
        m = 199;
        n = 199;

        int N = m*n;

        vector<array<int,2>> G[N+1];
        int seen[N];memset(seen,0,sizeof seen);

        // we start the robot at [99,99]
        int i = 99, j = 99;
        int d = explore(master,i,j,seen,G); // destination
        if( d == -1 ) return -1;
        int s = i*n+j;                      // source
        return shortestPath(N,G,s,d);
    }
};
