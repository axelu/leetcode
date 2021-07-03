
// 542. 01 Matrix
// https://leetcode.com/problems/01-matrix/




class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> ans(m,vector<int>(n,INT_MAX));

        // directions
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};

        // BFS
        queue<array<int,3>> q;
        int seen[m][n];memset(seen,0,sizeof seen);
        int i,j,r,c,step,k,r_new,c_new;

        for(i = 0; i < m; ++i) {
            for(j = 0; j < n; ++j) {
                if( mat[i][j] == 0 ) {
                    q.push({i,j,0});
                    seen[i][j] = 1;
                }
            }
        }

        while(!q.empty()) {
            r    = q.front()[0];
            c    = q.front()[1];
            step = q.front()[2];
            q.pop();

            if( ans[r][c] <= step ) continue;

            ans[r][c] = step;

            // explore in all directions
            for(int k = 0; k < 4; ++k) {

                r_new = r+dirR[k];
                if( r_new < 0 || r_new >= m )
                    continue;

                c_new = c+dirC[k];
                if( c_new < 0 || c_new >= n )
                    continue;

                // have we seen this cell before?
                if( seen[r_new][c_new] )
                    continue;

                seen[r_new][c_new] = 1;
                q.push({r_new,c_new,step+1});
            }
        }
        return ans;
    }
};
