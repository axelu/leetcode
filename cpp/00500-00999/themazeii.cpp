
// 505. The Maze II
// https://leetcode.com/problems/the-maze-ii/






class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size();
        int n = maze[0].size();

        // directions
        int dirR[4] = {0, 1, 0,-1};
        int dirC[4] = {1, 0,-1, 0};
        int dirM[4] = {0, 1, 2, 3};
        //             R  D  L  U   direction in which we are leaving a given cell

        // BFS
        int seen[m*n][4];memset(seen,0,sizeof seen);
        queue<array<int,4>> q;

        // getting started
        int i = start[0];
        int j = start[1];
        int i_new,j_new,k;
        for(k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new >= m )
                continue;

            j_new = j+dirC[k];
            if( j_new < 0 || j_new >= n )
                continue;

            // obstacle?
            if( maze[i_new][j_new] == 1 )
                continue;

            seen[i*n+j][k] = 1;
            q.push({i_new,j_new,k,1});
        }

        int step;
        bool didStop;
        while(!q.empty()) {
            i    = q.front()[0];
            j    = q.front()[1];
            k    = q.front()[2];
            step = q.front()[3];
            q.pop();

            didStop = false;

            i_new = i+dirR[k];
            if( i_new < 0 || i_new >= m )
                didStop = true;

            j_new = j+dirC[k];
            if( j_new < 0 || j_new >= n )
                didStop = true;

            // obstacle?
            if( !didStop )
                if( maze[i_new][j_new] == 1 )
                    didStop = true;

            if( didStop ) {
                // cout << "stopped" << endl;
                // destination?
                if( i == destination[0] && j == destination[1] )
                    return step;

                // choose a new direction
                for(int p = 0; p < 4; ++p) {
                    if( p == k ) continue; // skip the direction we were travling in

                    i_new = i+dirR[p];
                    if( i_new < 0 || i_new >= m )
                        continue;

                    j_new = j+dirC[p];
                    if( j_new < 0 || j_new >= n )
                        continue;

                    // obstacle
                    if( maze[i_new][j_new] == 1 )
                        continue;

                    // have we left the current cell in this direction before?
                    if( seen[i*n+j][p] )
                        continue;

                    seen[i*n+j][p] = 1;
                    q.push({i_new,j_new,p,step+1});
                }

            } else {
                // keep going
                seen[i*n+j][k] = 1;
                q.push({i_new,j_new,k,step+1});
            }
        }
        return -1;
    }
};
