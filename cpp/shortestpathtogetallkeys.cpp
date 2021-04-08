
// 864. Shortest Path to Get All Keys
// https://leetcode.com/problems/shortest-path-to-get-all-keys/



class Solution {
private:
    // debug
    void printState(int state) {
        for(int i = 5; i >= 0; --i) {
            int bit = (state >> i) & 1;
            cout << bit << " ";
        }
        cout << endl;
    }

public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        // # is wall
        // @ is starting point
        // . is empty cell
        // a,b,c,d,e,f are keys
        // A,B,C,D,E,F are locks
        // number of keys is in [1, 6]

        // to know if we aqcuired all keys, we need to have an inventory of them
        //   we will use a bit mask to store which keys are in the grid:
        //     Least Significant Bit (LSB) for key 'a', and so on,
        //     respectively using rightmost 6 bits (2^6 combinations aka states)
        // we also need to know where to start
        int keysInGrid = 0; // bitmask
        int rs = -1, cs = -1; // starting row and starting col
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                if( islower(grid[i][j]) )
                    keysInGrid |= 1 << (grid[i][j]-'a');
                if( grid[i][j] == '@' ) {
                    rs = i;
                    cs = j;
                }
            }
        // no keys
        if( keysInGrid == 0 ) return 0;

        // debug
        // cout << "keysInGrid ";
        // printState(keysInGrid);

        // Breadth First Search (BFS)
        // we need to not just mark if we have seen a given cell already,
        // but we need to mark it as seen with the keys we had at that moment, aka state,
        // meaning if we come back to the same cell with a DIFFERENT state, we will explore it [again]
        // as there are 6 keys and we are using a bitmask, there are 2^6 = 64 possible states
        // long is 64bit, so we can use the bits to indicate if we have seen a cell with state 0-63

        long seen[m][n]; memset(seen,0,sizeof seen); // stores a bitmask !!!

        // direction right, down, left, up
        int dirR[] = {0,1,0,-1};
        int dirC[] = {1,0,-1,0};

        queue<array<int,4>> q; // row,col,steps,state
        q.push({rs,cs,0,0});
        seen[rs][cs] = 1L; // mark starting point as seen with 'zero keys state'
        int row,row_new,col,col_new,steps,state,state_new;
        while( !q.empty() ) {
            row   = q.front()[0];
            col   = q.front()[1];
            steps = q.front()[2];
            state = q.front()[3];
            q.pop();
            // cout << "row " << row << " col " << col << " steps " << steps << " state ";
            // printState(state);

            // explore in all four directions
            for(int i = 0; i < 4; ++i) {

                row_new = row + dirR[i];
                if( row_new < 0 || row_new >= m )
                    continue;
                col_new = col + dirC[i];
                if( col_new < 0 || col_new >= n )
                    continue;

                // is the cell a wall?
                if( grid[row_new][col_new] == '#' )
                    continue;

                // have we seen this cell with the current state before?
                if( (seen[row_new][col_new] >> state) & 1L ) continue;

                // is the cell empty or starting point?
                if( grid[row_new][col_new] == '.' || grid[row_new][col_new] == '@' ) {
                    seen[row_new][col_new] |= 1L << state;
                    q.push({row_new,col_new,steps+1,state});
                }

                // is the cell a lock?
                if( isupper(grid[row_new][col_new]) ) {
                    // do we have the key for this lock?
                    if( (state >> grid[row_new][col_new]-'A') & 1 ) {
                        seen[row_new][col_new] |= 1L << state;
                        q.push({row_new,col_new,steps+1,state});
                    }
                }

                // is the cell a key?
                if( islower(grid[row_new][col_new]) ) {
                    // collect the key = new state;
                    state_new = state;
                    state_new |= 1 << (grid[row_new][col_new]-'a');

                    // do we have all keys?
                    if( state_new == keysInGrid ) return steps+1;

                    // mark cell as seen in the current state
                    seen[row_new][col_new] |= 1L << state;

                    q.push({row_new,col_new,steps+1,state_new});
                }
            }
        }
        return -1;
    }
};
