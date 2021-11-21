
// 361. Bomb Enemy
// https://leetcode.com/problems/bomb-enemy/





class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int i,j,c,ans=0;

        // line sweep rows
        vector<vector<int>> cnt(m,vector<int>(n,0));
        for(i = 0; i < m; ++i) {
            // right to left
            c = 0;
            for(j = n-1; j >= 0; --j)
                if( grid[i][j] == 'E' )
                    ++c;
                else if( grid[i][j] == 'W' )
                    c = 0;
                else if( grid[i][j] == '0' )
                    cnt[i][j] = c;
            // left to right
            c = 0;
            for(j = 0; j < n; ++j)
                if( grid[i][j] == 'E' )
                    ++c;
                else if( grid[i][j] == 'W' )
                    c = 0;
                else if( grid[i][j] == '0' )
                    cnt[i][j] = cnt[i][j]+c;
        }

        // line sweep columns
        vector<vector<int>> cols(m,vector<int>(n));
        for(j = 0; j < n; ++j) {
            // bottom to top
            c = 0;
            for(i = m-1; i >= 0; --i)
                if( grid[i][j] == 'E' )
                    ++c;
                else if( grid[i][j] == 'W' )
                    c = 0;
                else if( grid[i][j] == '0' )
                    cnt[i][j] = cnt[i][j]+c;
            // top to bottom
            c = 0;
            for(i = 0; i < m; ++i)
                if( grid[i][j] == 'E' )
                    ++c;
                else if( grid[i][j] == 'W' )
                    c = 0;
                else if( grid[i][j] == '0' ) {
                    cnt[i][j] = cnt[i][j]+c;
                    ans = max(ans,cnt[i][j]);
                }
        }

        return ans;
    }
};
