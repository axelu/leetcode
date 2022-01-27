
// 711. Number of Distinct Islands II
// https://leetcode.com/problems/number-of-distinct-islands-ii/



class Solution {
private:
    void explore(int row, int col, vector<vector<int>>& grid,
        int seen[], string& shape, char dir, vector<int>& area) {

        int m = grid.size();
        int n = grid[0].size();

        if( grid[row][col] == 0 ) return;   // water
        int seenIdx = row*n+col;
        if( seen[seenIdx] == 1 ) return;    // land we have seen before
        seen[seenIdx] = 1;                  // mark land as seen
        shape += dir;

        if( row < area[0] ) area[0] = row;
        if( col < area[1] ) area[1] = col;
        if( row > area[2] ) area[2] = row;
        if( col > area[3] ) area[3] = col;

        // right
        if( col < n-1 ) explore(row,col+1,grid,seen,shape,'R',area);
        // down
        if( row < m-1 ) explore(row+1,col,grid,seen,shape,'D',area);
        // left
        if( col > 0 ) explore(row,col-1,grid,seen,shape,'L',area);
        // up
        if( row > 0 ) explore(row-1,col,grid,seen,shape,'U',area);

        shape += 'B';
    }

    vector<vector<int>> getSubGrid(vector<vector<int>>& grid,
        int row_min,int col_min, int row_max, int col_max) {

        int m = row_max-row_min+1; // number rows
        int n = col_max-col_min+1; // number cols
        vector<vector<int>> ans = vector(m,vector<int>(n));
        int k = 0, l = 0;
        for(int i = row_min; i <= row_max; ++i) {
            for(int j = col_min; j <= col_max; ++j) {
                ans[k][l] = grid[i][j];
                ++l;
            }
            l = 0;
            ++k;
        }
        return ans;
    }

    vector<vector<int>> rot90(vector<vector<int>>& grid) {
        int m = grid.size();    // number rows of grid to rotate = number cols of rotated grid
        int n = grid[0].size(); // number cols of grid to rotate = number rows of rotated grid
        vector<vector<int>> ans = vector(n,vector<int>(m));

        int k = 0;
        for(int j = 0; j < n; ++j) {
            for(int i = m-1; i >= 0; --i) {
                ans[j][k] = grid[i][j];
                ++k;
            }
            k = 0;
        }
        return ans;
    }

    vector<vector<int>> flipVertical(vector<vector<int>>& grid) {
        int m = grid.size();    // number rows
        int n = grid[0].size(); // number cols
        vector<vector<int>> ans = vector(m,vector<int>(n));

        int l,r,t;
        for(int i = 0; i < m; ++i) {
            l = 0;
            r = n-1;
            while(l < r) {
                t = grid[i][l];
                ans[i][l] = grid[i][r];
                ans[i][r] = t;
                ++l;
                --r;
            }
        }
        return ans;
    }

    vector<vector<int>> flipHorizontal(vector<vector<int>>& grid) {
        int m = grid.size();    // number rows
        int n = grid[0].size(); // number cols
        vector<vector<int>> ans = vector(m,vector<int>(n));

        int t,b,tmp;
        for(int j = 0; j < n; ++j) {
            t = 0;
            b = m-1;
            while(t < b) {
                tmp = grid[t][j];
                ans[t][j] = grid[b][j];
                ans[b][j] = tmp;
                ++t;
                --b;
            }
        }
        return ans;
    }

public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        int m = grid.size();
        if( m == 0 ) return 0;
        int n = grid[0].size();
        if( m == 1 && n == 1 )
            return grid[0][0] == 1 ? 1 : 0;

        int seen[m*n]; memset(seen,0,sizeof seen);
        unordered_set<string> shapes;
        string shape;
        int ans = 0;
        int row_min,col_min,row_max,col_max;
        vector<int> area(4); // row_min,col_min,row_max,col_max
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 && !seen[i*n+j] ) { // land we have not seen before
                    shape = "";
                    area[0]=i;area[1]=j;area[2]=i;area[3]=j;
                    explore(i,j,grid,seen,shape,'S',area);
                    cout << shape << endl;
                    if( shapes.insert(shape).second ) {
                        // we have not seen this shape before
                        ++ans;
                        // record all rotations and reflections of this shape
                        // create new grid of the area that covers this shape
                        row_min = area[0];
                        col_min = area[1];
                        row_max = area[2];
                        col_max = area[3];
                        vector<vector<int>> grid2 = getSubGrid(grid,row_min,col_min,row_max,col_max);
                        // rotate subgrid 90deg and explore it
                        grid2 = rot90(grid2);
                        int ti = j-col_min;
                        int tj = grid2[0].size()-1;
                        int seen90[grid2.size()*grid2[0].size()];memset(seen90,0,sizeof seen90);
                        shape = "";
                        explore(ti,tj,grid2,seen90,shape,'S',area);
                        cout << shape << " 90" << endl;
                        shapes.insert(shape);
                        // rotate subgrid 90deg and explore it = 180deg
                        grid2 = rot90(grid2);
                        ti = grid2.size()-1;
                        tj = grid2[0].size()-1-(j-col_min);
                        int seen180[grid2.size()*grid2[0].size()];memset(seen180,0,sizeof seen180);
                        shape = "";
                        explore(ti,tj,grid2,seen180,shape,'S',area);
                        cout << shape << " 180" << endl;
                        shapes.insert(shape);
                        // rotate subgrid 90deg and explore it = 270deg
                        grid2 = rot90(grid2);
                        ti = grid2.size()-1-(j-col_min);
                        tj = 0;
                        memset(seen90,0,sizeof seen90);
                        shape = "";
                        explore(ti,tj,grid2,seen90,shape,'S',area);
                        cout << shape << " 270" << endl;
                        shapes.insert(shape);
                        // rotate subgrid 90deg to restore = 360deg
                        grid2 = rot90(grid2);
                        // reflect left/right
                        grid2 = flipVertical(grid2);
                        ti = 0;
                        tj = grid2[0].size()-1-(j-col_min);
                        memset(seen180,0,sizeof seen180);
                        shape = "";
                        explore(ti,tj,grid2,seen180,shape,'S',area);
                        cout << shape << " flip vertical" << endl;
                        shapes.insert(shape);
                        grid2 = flipVertical(grid2); // flip to restore
                        // TODO reflect up/down
                        grid2 = flipHorizontal(grid2);
                        ti = grid2.size()-1;
                        tj = j-col_min;
                        memset(seen180,0,sizeof seen180);
                        shape = "";
                        explore(ti,tj,grid2,seen180,shape,'S',area);
                        cout << shape << " flip horizontal" << endl;
                        shapes.insert(shape);


                    }
                }
        return ans;

    }
};
