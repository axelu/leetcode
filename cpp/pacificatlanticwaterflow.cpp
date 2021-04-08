
// 417. Pacific Atlantic Water Flow
// https://leetcode.com/problems/pacific-atlantic-water-flow/
// day 25 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/591/week-4-march-22nd-march-28th/3684/





class Solution {
private:
    int m,n; // rows,cols

    // debug
    void printMatrix(int matrix[]) {
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << matrix[i*n+j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    void printMatrix(vector<vector<int>>& matrix) {
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // direction right,down,left,up
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    int getState(int i, int j, int can[], int bt) {
        // the state is determined by the 4 sourrounding cells
        int state = 0; // there are 16 states (0-15, based on 4 sourrounding cells 2^4)
        int i_new,j_new;
        for(int k = 0; k < 4; ++k) {
            i_new = i + dirR[k];
            if( i_new < 0 || i_new > m-1 ) continue;
            j_new = j + dirC[k];
            if( j_new < 0 || j_new > n-1 ) continue;
            if( (can[i_new*n+j_new] >> bt) & 1 )
                state |= 1 << k;
        }
        return state;
    }

    bool dfs(int i, int j, int seen[], int can[], int bt, vector<vector<int>>& matrix) {
        int idx = i*n+j;
        if( (can[idx] >> bt) & 1 )
            return true;

        // has the cell been seen in the current state?
        int state = getState(i,j,can,bt);
        if( (seen[i*n+j] >> state) & 1 ) return false;

        // mark cell as seen in the current state
        seen[idx] |= 1 << state;

        // explore all four directions
        bool res[] = {false,false,false,false};
        int i_new,j_new;
        for(int k = 0; k < 4; ++k) {
            i_new = i + dirR[k];
            if( i_new < 0 || i_new > m-1 ) continue;
            j_new = j + dirC[k];
            if( j_new < 0 || j_new > n-1 ) continue;

            // can water flow to this new cell?
            if( matrix[i_new][j_new] > matrix[i][j] ) continue;

            res[k] = dfs(i_new,j_new,seen,can,bt,matrix);
        }

        if( res[0] || res[1] || res[2] || res[3] ) {
            can[idx] |= 1 << bt;
            return true;
        }
        return false;
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        m = matrix.size();
        if( m == 0 ) return {};
        n = matrix[0].size();

        // printMatrix(matrix);

        // each cell is a starting point to reach pacific and atlantic

        // DFS
        int seen[m*n]; // bit mask
        int state;
        int can[m*n]; memset(can,0,sizeof can); // bit mask

        // can reach atlantic, using right most bit
        for(int i = 0; i < m; ++i) can[i*n+(n-1)] |= 1;
        for(int j = 0; j < n; ++j) can[(m-1)*n+j] |= 1;
        memset(seen,0,sizeof seen);
        for(int i = 0; i < m-1; ++i)
            for(int j = 0; j < n-1; ++j) {
                // determine state
                state = getState(i,j,can,0);
                // has the cell been seen in this state?
                if( !((seen[i*n+j] >> state) & 1) ) {
                    // cout << "not seen in this state " << i << " " << j << endl;
                    dfs(i,j,seen,can,0,matrix);
                }
            }

        // printMatrix(can);

        // can reach pacific, using second from the right bit
        for(int i = 0; i < m; ++i) can[i*n] |= 1 << 1;
        for(int j = 0; j < n; ++j) can[j] |= 1 << 1;
        memset(seen,0,sizeof seen);
        for(int i = m-1; i > 0; --i)
            for(int j = n-1; j > 0; --j) {
                // determine state
                state = getState(i,j,can,1);
                // has the cell been seen in this state?
                if( !((seen[i*n+j] >> state) & 1) ) {
                    // cout << "not seen in this state " << i << " " << j << endl;
                    dfs(i,j,seen,can,1,matrix);
                }
            }

        vector<vector<int>> ans;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                // cout << can[i*n+j] << " ";
                if( can[i*n+j] == 3 ) ans.push_back({i,j});
            }
            // cout << endl;
        }
        return ans;
    }
};
