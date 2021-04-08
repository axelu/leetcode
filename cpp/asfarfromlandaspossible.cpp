
// 1162. As Far from Land as Possible
// https://leetcode.com/problems/as-far-from-land-as-possible/



class Solution {
private:
    int N;
    int ans;
    bool hasWater;
    bool hasLand;

    void swim(int row, int col, vector<vector<int>>& grid, int swam[]) {
        int swamIdx = row*N+col;
        if( swam[swamIdx] == 1 ) return;

        // BFS
        int seen[N*N]; memset(seen,0,sizeof seen);
        queue<array<int,3>> q;
        array<int,3> qe;
        int currRow,currCol,currDepth,seeIdx;
        q.push({row,col,1});
        seen[row*N+col] = 1;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            currRow = qe[0];
            currCol = qe[1];
            currDepth = qe[2];
            // have we been here from a closer land cell?
            if( swam[currRow*N+currCol] <= currDepth ) continue;
            swam[currRow*N+currCol] = currDepth;
            // up
            if( currRow > 0 && grid[currRow-1][currCol] == 0 && !seen[(currRow-1)*N+currCol] ) {
                q.push({currRow-1,currCol,currDepth+1});
                seen[(currRow-1)*N+currCol] = 1;
            }
            // right
            if( currCol < N-1 && grid[currRow][currCol+1] == 0 && !seen[currRow*N+(currCol+1)] ) {
                q.push({currRow,currCol+1,currDepth+1});
                seen[currRow*N+(currCol+1)] = 1;
            }
            // down
            if( currRow < N-1 && grid[currRow+1][currCol] == 0 && !seen[(currRow+1)*N+currCol] ) {
                q.push({currRow+1,currCol,currDepth+1});
                seen[(currRow+1)*N+currCol] = 1;
            }
            // left
            if( currCol > 0 && grid[currRow][currCol-1] == 0 && !seen[currRow*N+(currCol-1)] ) {
                q.push({currRow,currCol-1,currDepth+1});
                seen[currRow*N+(currCol-1)] = 1;
            }
        }
    }

    void explore(int row, int col, vector<vector<int>>& grid, int seen[], int swam[]) {
        if( grid[row][col] == 0 ) { // water
            hasWater = true;
            swim(row,col,grid,swam);
            return;
        }
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;    // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen
        swam[seenIdx] = INT_MIN;

        // right
        if( col < N-1 ) explore(row,col+1,grid,seen,swam);
        // down
        if( row < N-1 ) explore(row+1,col,grid,seen,swam);
        // left
        if( col > 0 ) explore(row,col-1,grid,seen,swam);
        // up
        if( row > 0 ) explore(row-1,col,grid,seen,swam);
    }

public:
    int maxDistance(vector<vector<int>>& grid) {
        N = grid.size();
        if( N == 1 ) return -1;

        hasLand = false;
        hasWater = false;
        ans = 0;
        int seen[N*N];
        int swam[N*N];
        int idx;
        for(int i = 0; i < N*N; ++i) {
            seen[i] = 0;
            swam[i] = INT_MAX;
        }
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if( grid[i][j] == 1 && seen[i*N+j] == 0 ) { // land we have NOT seen before
                    hasLand = true;
                    explore(i,j,grid,seen,swam);
                }

        if( !hasLand || !hasWater ) return -1;
        return *max_element(swam,swam+N*N);
    }
};
