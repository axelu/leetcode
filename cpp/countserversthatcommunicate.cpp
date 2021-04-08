
// 1267. Count Servers that Communicate
// https://leetcode.com/problems/count-servers-that-communicate/




class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols
        if( m == 1 && n == 1 ) return 0;

        // pass 1
        // count servers in each row and column
        int serversPerRow[m]; memset(serversPerRow,0,sizeof serversPerRow);
        int serversPerCol[n]; memset(serversPerCol,0,sizeof serversPerCol);
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 ) {
                    ++serversPerRow[i];
                    ++serversPerCol[j];
                }

        int ans = 0;
        // pass 2
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 &&
                   ( serversPerRow[i] > 1 || serversPerCol[j] > 1 ) ) ++ans;

        return ans;
    }
};
