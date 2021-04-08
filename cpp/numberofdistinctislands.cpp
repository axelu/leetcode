
// 694. Number of Distinct Islands
// https://leetcode.com/problems/number-of-distinct-islands/
// day 8 February 2021 challenge bonus question
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3632/




class Solution {
private:
    int M,N;
    void explore(int row, int col, vector<vector<int>>& grid, int seen[], string& shape, char dir) {
        if( grid[row][col] == 0 ) return; // water
        int seenIdx = row*N+col;
        if( seen[seenIdx] == 1 ) return;    // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen
        shape += dir;

        // right
        if( col < N-1 ) explore(row,col+1,grid,seen,shape,'R');
        // down
        if( row < M-1 ) explore(row+1,col,grid,seen,shape,'D');
        // left
        if( col > 0 ) explore(row,col-1,grid,seen,shape,'L');
        // up
        if( row > 0 ) explore(row-1,col,grid,seen,shape,'U');

        shape += 'B';
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        M = grid.size();
        if( M == 0 ) return 0;
        N = grid[0].size();
        if( M == 1 && N == 1 )
            return grid[0][0] == 1 ? 1 : 0;

        int seen[M*N]; memset(seen,0,sizeof seen);
        unordered_set<string> shapes;
        string shape;
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < N; ++j)
                if( grid[i][j] == 1 && !seen[i*N+j] ) { // land we have not seen before
                    shape = "";
                    explore(i,j,grid,seen,shape,'S');
                    shapes.insert(shape);
                }
        return shapes.size();
    }
};
