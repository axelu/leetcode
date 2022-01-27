
// 1914. Cyclically Rotating a Grid
// https://leetcode.com/problems/cyclically-rotating-a-grid/





// TODO in place rotation
class Solution {
private:
    pair<int,int> advance(int i, int j, int m, int n) {
        if( j == 0 ) {
            ++i;
            if( i == m ) {
                i = m-1;
                j = 1;
            }
        } else if( i == m-1 ) {
            ++j;
            if( j == n ) {
                j = n-1;
                i = m-2;
            }
        } else if( j == n-1) {
            --i;
            if( i == -1 ) {
                i = 0;
                j = n-2;
            }
        } else {
            // i == 0
            --j;
        }
        return {i,j};
    }

public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();    // rows, 2 <= m <= 50, m is even
        int n = grid[0].size(); // cols, 2 <= n <= 50, n is even
        // printf("m %i n %i\n",m,n);

        int o_max = min(m,n)/2;
        int cells = 2*m + (2*n-4);  // number of cells in the layer

        vector<vector<int>> ans(m,vector<int>(n));

        int o = 0;
        for(; o < o_max; ++o) {   // layer
            int rot   = k%cells;
            // printf("o %i m %i n %i cells %i rotations %i\n",o,m,n,cells,rot);

            // rotate
            int i = 0,i_new,j = 0,j_new,r,r_new,c,c_new;
            // source
            r = i+o;
            c = j+o;
            // target
            if( rot < m ) {
                i_new = i+rot;
                j_new = 0;
            } else if( rot < m+n-1 ) {
                i_new = m-1;
                j_new = rot - (m-1);
            } else if( rot < m+n-1+m-1 ) {
                i_new = m+n-1+m-1-1 - rot;
                j_new = n-1;
            } else {
                i_new = 0;
                j_new = cells-rot;
            }
            r_new = i_new+o;
            c_new = j_new+o;

            for(int p = 0; p < cells; ++p) {
                // printf("i %i\tj %i \n",i,j);
                // printf("r\t%i\tc\t%i\n",r,c);                 // source
                // printf("r_new\t%i\tc_new\t%i\n",r_new,c_new); // target
                ans[r_new][c_new] = grid[r][c];

                tie(i,j) = advance(i,j,m,n);
                tie(i_new,j_new) = advance(i_new,j_new,m,n);

                r = i+o; r_new = i_new+o;
                c = j+o; c_new = j_new+o;

            }

            m     = m-2;
            n     = n-2;
            cells = 2*m + (2*n-4);
        }

        return ans;
    }
};
