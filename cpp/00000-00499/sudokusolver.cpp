
// 37. Sudoku Solver
// https://leetcode.com/problems/sudoku-solver/




class Solution {
private:
    int row[9];
    int col[9];
    int grid[9];

    vector<array<int,2>> ec; // empty cells

    bool dfs(int pos, vector<vector<char>>& board) {

        // get all possible options for the current cell
        int r = ec[pos][0];
        int c = ec[pos][1];
        int gridIdx = (r/3*3)+(c/3);
        vector<int> o;
        for(int i = 1; i <= 9; ++i)
            if( !((row[r] >> i) & 1) && !((col[c] >> i) & 1) && !((grid[gridIdx] >> i) & 1) )
                o.push_back(i);

        if( pos == ec.size()-1 ) {
            board[r][c] = o[0]+48;
            return true;
        }

        int val;
        for(int i = 0; i < o.size(); ++i) {
            val = o[i];

            row[r] |= 1 << val;
            col[c] |= 1 << val;
            grid[gridIdx] |= 1 << val;

            if( dfs(pos+1,board) ) {
                board[r][c] = val+48;
                return true;
            }

            // backtrack
            row[r] &= ~(1 << val);
            col[c]  &= ~(1 << val);
            grid[gridIdx] &= ~(1 << val);
        }

        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {

        // inventory the initial state of the board
        // and empty cells

        memset(row,0,sizeof row);
        memset(col,0,sizeof col);
        memset(grid,0,sizeof grid);

        int val,i,j;
        for(i = 0; i < 9; ++i)
            for(j = 0; j < 9; ++j) {

                if( isdigit(board[i][j]) ) {
                    val = board[i][j]-48;

                    row[i] |= 1 << val;
                    col[j] |= 1 << val;
                    grid[(i/3*3)+(j/3)] |= 1 << val;

                } else {
                    ec.push_back({i,j});
                }
            }

        dfs(0,board);
    }
};
