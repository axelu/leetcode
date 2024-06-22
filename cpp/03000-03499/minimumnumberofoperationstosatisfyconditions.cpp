
// 3122. Minimum Number of Operations to Satisfy Conditions
// https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/






class Solution {
private:
    int rec(int m, int n, int j, int pre, int colcnt[][10], int mem[][10]) {
        if( j == n )
            return 0;

        if( pre != -1 && mem[j][pre] != -1 )
            return mem[j][pre];

        // we have a choice
        //    change the current column to anything other than the prior column

        int ret = 1000000000;

        for(int k = 0; k < 10; ++k) {
            if( k == pre )
                continue;

            // cost to change the current column to k
            int cost = m - colcnt[j][k];
            ret = min(ret, cost + rec(m, n, j+1, k, colcnt, mem));
        }

        if( pre != -1 )
            mem[j][pre] = ret;

        return ret;
    }


public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int colcnt[n][10];memset(colcnt,0,sizeof colcnt);
        for(int j = 0; j < n; ++j)
            for(int i = 0; i < m; ++i)
                ++colcnt[j][grid[i][j]];

        int mem[n][10];memset(mem,-1,sizeof mem);
        return rec(m, n, 0, -1, colcnt, mem);
    }
};
