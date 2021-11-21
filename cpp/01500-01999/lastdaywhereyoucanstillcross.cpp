
// 1970. Last Day Where You Can Still Cross
// https://leetcode.com/problems/last-day-where-you-can-still-cross/




class Solution {
private:
    int m,n,state;

    // debug
    void printGrid(vector<vector<int>>& grid) {
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j)
                cout << grid[i][j] << " ";
            cout << endl;
        }
    }

    // four directions down,right,left,up
    int dirR[4] = {1,0,0,-1};
    int dirC[4] = {0,1,-1,0};

    bool canCross(vector<vector<int>>& grid, vector<vector<int>>& cells, int day) {
        // the grid is in state
        // so we need to update the grid from state to day
        if( state < day )
            for(int i = state + 1; i <= day; ++i)
                grid[cells[i][0]-1][cells[i][1]-1] = 1;
        else if( state > day )
            for(int i = state; i > day; --i)
                grid[cells[i][0]-1][cells[i][1]-1] = 0;
        state = day;

        // BFS starting from every land cell in row 0 to reach a cell in row m-1
        queue<array<int,2>> q;
        int seen[m][n];memset(seen,0,sizeof seen);
        for(int j = 0; j < n; ++j)
            if( grid[0][j] == 0 ) {
                q.push({0,j});
                seen[0][j] = 1;
            }
        int i,j,i_new,j_new;
        while( !q.empty() ) {
            i = q.front()[0];
            j = q.front()[1];
            q.pop();


            // explore all for directions
            for(int k = 0; k < 4; ++k) {
                i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;
                j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                if( grid[i_new][j_new] == 1 )
                    continue;

                if( seen[i_new][j_new] == 1 )
                    continue;

                if( i_new == m-1 )
                    return true;

                seen[i_new][j_new] = 1;
                q.push({i_new,j_new});
            }
        }
        return false;
    }

    int search(int s, int e, vector<vector<int>>& grid, vector<vector<int>>& cells) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = canCross(grid,cells,mid);
        if( f ) {
            // can we do better?
            int t = search(mid+1,e,grid,cells);
            return t != -1 ? t : mid;
        } else {
            return search(s,mid-1,grid,cells);
        }
    }

public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        m = row;
        n = col;
        // int n = cells.size(); // days really

        // our ans is between 1 and n inclusive
        vector<vector<int>> grid(row,vector<int>(col,0));
        grid[cells[0][0]-1][cells[0][1]-1] = 1;
        state = 0; // initially the grid is in state day 0 (offset 1)

        return search(0,cells.size()-1,grid,cells)+1;
    }
};
