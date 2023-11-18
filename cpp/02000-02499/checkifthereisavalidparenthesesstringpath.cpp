
// 2267. Check if There Is a Valid Parentheses String Path
// https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/




class Solution {
private:
    int stck;
    int m,n;

    int mem[201][100][100];

    bool rec(vector<vector<char>>& grid, int i, int j) {
        if( stck == 0 && grid[i][j] == ')' )
            return false;

        if( mem[stck][i][j] != -1 )
            return mem[stck][i][j];

        bool pushed = false;

        if( grid[i][j] == '(' ) {
            ++stck;
            pushed = true;
        } else {
            --stck;
        }


        if( i == m-1 && j == n-1 && stck == 0 )
            return true;

        // go down
        int i_new = i + 1;
        if( i_new < m && rec(grid,i_new,j) )
            return true;

        // go right
        int j_new = j + 1;
        if( j_new < n && rec(grid,i,j_new) )
            return true;

        // backtrack
        if( pushed )
            --stck;
        else
            ++stck;

        return mem[stck][i][j] = false;
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols

        memset(mem,-1,sizeof mem);
        stck = 0;
        return rec(grid,0,0);
    }
};
