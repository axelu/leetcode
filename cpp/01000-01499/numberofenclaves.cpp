
// 1020. Number of Enclaves
// https://leetcode.com/problems/number-of-enclaves/


class Solution {
private:
    int m,n;

    // four directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    int rec(vector<vector<int>>& grid, int i, int j, int seen[]) {
        int seenIdx = i*n+j;
        seen[seenIdx] = 1;

        int cnt = 1; // number of cells in this island
        bool boundary = false;

        // BFS
        queue<array<int,2>> q;
        q.push({i,j});
        int i_new,j_new;
        while( !q.empty() ) {
            i = q.front()[0];
            j = q.front()[1];
            q.pop();

            // explore all directions
            for(int k = 0; k < 4; ++k) {
                i_new = i + dirR[k];
                if( i_new < 0 || i_new == m ) {
                    boundary = true;
                    continue;
                }
                j_new = j + dirC[k];
                if( j_new < 0 || j_new == n ) {
                    boundary = true;
                    continue;
                }

                if( grid[i_new][j_new] == 0 )
                    continue;

                seenIdx = i_new*n+j_new;
                if( seen[seenIdx] )
                    continue;

                seen[seenIdx] = 1;
                ++cnt;
                q.push({i_new,j_new});
            }
        }

        return boundary ? 0 : cnt;
    }


public:
    int numEnclaves(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols
        if( m == 1 || n == 1 )
            return 0;

        int ans = 0;

        int seen[m*n];memset(seen,0,sizeof seen);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 && !seen[i*n+j] ) // land we have not seen
                    ans += rec(grid,i,j,seen);

        return ans;
    }
};
