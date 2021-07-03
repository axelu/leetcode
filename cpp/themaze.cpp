
// 490. The Maze
// https://leetcode.com/problems/the-maze/




class Solution {
private:
    int m,n;

    // directions
    int dirR[4] = {0, 1, 0,-1};
    int dirC[4] = {1, 0,-1, 0};
    int dirM[4] = {0, 1, 2, 3};
    //             R  D  L  U   direction in which we are leaving a given cell

    bool dfs(vector<vector<int>>& maze, int i, int j, vector<int>& destination, int seen[][4], int k) {
        // cout << "dfs i " << i << " j " << j << " k " << k << endl;
        int i_new,j_new;

        bool didStop = false;

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
                return true;

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
                if( dfs(maze,i_new,j_new,destination,seen,p) )
                    return true;
            }

        } else {
            // keep going
            seen[i*n+j][k] = 1;
            return dfs(maze,i_new,j_new,destination,seen,k);
        }
        return false;
    }

public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        m = maze.size();
        n = maze[0].size();

        int seen[m*n][4];memset(seen,0,sizeof seen);

        // getting started
        int i = start[0];
        int j = start[1];
        int i_new,j_new;
        for(int k = 0; k < 4; ++k) {

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
            if( dfs(maze,i_new,j_new,destination,seen,k) )
                return true;
        }

        return false;
    }
};
