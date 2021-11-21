
// 1905. Count Sub Islands
// https://leetcode.com/problems/count-sub-islands/



class Solution {
private:
    int m,n;

    // four directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    bool explore(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int r, int c,
                 int seen[]) {

        int seenIdx = r*n+c;
        seen[seenIdx] = 1;

        bool ret = true;

        queue<array<int,2>> q;
        q.push({r,c});
        int i,i_new,j,j_new;
        while( !q.empty() ) {
            i = q.front()[0];
            j = q.front()[1];
            q.pop();

            // explore all four directions
            for(int k = 0; k < 4; ++k) {
                i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;
                j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                if( grid2[i_new][j_new] == 0 )
                    continue;

                if( grid1[i_new][j_new] == 0 )
                    ret = false; // continue to mark island as seen

                seenIdx = i_new*n+j_new;
                if( seen[seenIdx] )
                    continue;

                seen[seenIdx] = 1;
                q.push({i_new,j_new});
            }
        }

        return ret;
    }

public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        m = grid1.size();
        n = grid1[0].size();

        int ans = 0;

        int seen[m*n];memset(seen,0,sizeof seen);
        int seenIdx;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                seenIdx = i*n+j;
                if( grid2[i][j] == 1 && grid1[i][j] == 1 && !seen[seenIdx] ) {
                    ans += explore(grid1,grid2,i,j,seen);
                }
            }
        }

        return ans;
    }
};
