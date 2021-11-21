
// 36. Valid Sudoku
// https://leetcode.com/problems/valid-sudoku/





class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {


        int col[9][10];memset(col,0,sizeof col);
        int grid[9][10];memset(grid,0,sizeof grid);

        int currRow[10];
        int gridIdx,val;
        for(int i = 0; i < 9; ++i) {            // rows
            memset(currRow,0,sizeof currRow);
            for(int j = 0; j < 9; ++j) {        // cols

                if( isdigit(board[i][j]) ) {
                    val = board[i][j]-48;

                    ++currRow[val];
                    if( currRow[val] == 2 )
                        return false;

                    ++col[j][val];
                    if( col[j][val] == 2 )
                        return false;

                    // what grid are we in?
                    gridIdx = (i/3*3)+(j/3);
                    ++grid[gridIdx][val];
                    if( grid[gridIdx][val] == 2 )
                        return false;
                }
            }
        }

        return true;
    }
};
