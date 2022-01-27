
// 959. Regions Cut By Slashes
// https://leetcode.com/problems/regions-cut-by-slashes/



class Solution {
private:
    int m;
    int mat[60][60];

    // directions right,down,left,up
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    void dfs(int i, int j) {
        mat[i][j] = 1;

        int i_new,j_new;
        // explore in all four directions
        for(int k = 0; k < 4; ++k) {
            i_new = i + dirR[k];
            if( i_new < 0 || i_new == m*2 ) continue;
            j_new = j + dirC[k];
            if( j_new < 0 || j_new == m*2 ) continue;

            if( mat[i_new][j_new] == 0 )
                dfs(i_new,j_new);
        }

        // additionally, we can explore diagonally
        if( (i%2 == 0 && j%2 == 1) || (i%2 == 1 && j%2 == 0 ) ) {
            // cell with backslash in original grid
            // we can explore north-west and south-east
            // north-west
            i_new = i-1;
            j_new = j-1;
            if( i_new >= 0 && j_new >= 0 && mat[i_new][j_new] == 0 )
                dfs(i_new,j_new);
            // south-east
            i_new = i+1;
            j_new = j+1;
            if( i_new < m*2 && j_new < m*2 && mat[i_new][j_new] == 0 )
                dfs(i_new,j_new);
        }

        if( (i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1 ) ) {
            // cell with forward slash in original grid
            // we can explore north-east and south-west
            // north-east
            i_new = i-1;
            j_new = j+1;
            if( i_new >= 0 && j_new < m*2 && mat[i_new][j_new] == 0 )
                dfs(i_new,j_new);
            // south-west
            i_new = i+1;
            j_new = j-1;
            if( i_new < m*2 && j_new >= 0 && mat[i_new][j_new] == 0 )
                dfs(i_new,j_new);
        }
    }

public:
    int regionsBySlashes(vector<string>& grid) {
        // 1 <= grid.length == grid[0].length <= 30
        m = grid.size();

        memset(mat,0,sizeof mat);
        int i,j,x,y;
        for(i = 0; i < m; ++i) {
            x = i*2;
            for(j = 0; j < m; ++j) {
                y = j*2;
                if( grid[i][j] == '/' ) {
                    mat[x][y+1]   = 2;
                    mat[x+1][y]   = 2;
                } else if( grid[i][j] == '\\' ) {
                    mat[x][y]     = 2;
                    mat[x+1][y+1] = 2;
                }
            }
        }
        /*
        for(i = 0; i < m*2; ++i) {
            for(j = 0; j < m*2; ++j) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        */
        // each cell could be the starting point of a new region
        int ans = 0;
        for(i = 0; i < m*2; ++i) {
            for(j = 0; j < m*2; ++j) {
                if( mat[i][j] == 0 ) {
                    dfs(i,j);
                    ++ans;
                }
            }
        }

        return ans;
    }
};
