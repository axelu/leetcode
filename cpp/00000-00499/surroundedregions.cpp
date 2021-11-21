
// 130. Surrounded Regions
// https://leetcode.com/problems/surrounded-regions/




class Solution {
private:

    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    bool explore(vector<vector<char>>& grid, int m, int n, int i, int j,
                 int seen[], vector<vector<int>>& region) {

        // return true if connected to a border cell
        // cout << "i " << i << " j " << j << endl;

        bool res = false;
        if( i == 0 || i == m-1 || j == 0 || j == n-1 )
            res = true;

        int seenIdx = i*n+j;
        seen[seenIdx] = 1;
        region.push_back({i,j});

        int i_new,j_new;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new == m )
                continue;

            j_new = j+dirC[k];
            if( j_new < 0 || j_new == n )
                continue;

            // X?
            if( grid[i_new][j_new] == 'X' )
                continue;

            // O cell we have seen before?
            if( seen[i_new*n+j_new] )
                continue;

            if( explore(grid,m,n,i_new,j_new,seen,region) )
                res = true;
        }
        return res;
    }

public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        if( m <= 2 || n <= 2 )
            return;

        int seen[m*n];memset(seen,0,sizeof seen);
        vector<vector<int>> capture;
        for(int i = 1; i < m-1; ++i)
            for(int j = 1; j < n-1; ++j)
                if( board[i][j] == 'O' && !seen[i*n+j] ) { // region we have not seen
                    vector<vector<int>> region;
                    bool res = explore(board,m,n,i,j,seen,region);
                    if( !res )
                       for(int k = 0; k < region.size(); ++k)
                           capture.push_back(region[k]);
                }

        // capture
        for(int i = 0; i < capture.size(); ++i)
            board[capture[i][0]][capture[i][1]] = 'X';
    }
};
