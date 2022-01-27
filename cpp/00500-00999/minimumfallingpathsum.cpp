
// 931. Minimum Falling Path Sum
// https://leetcode.com/problems/minimum-falling-path-sum/




class Solution {
private:
    int mem[101][101];

    int rec(vector<vector<int>>& matrix, int n, int r, int c) {
        if( r == n )
            return 0;

        if( mem[r][c] != -1 )
            return mem[r][c];

        // we have three choices
        int nxt[3] = {-1,0,1};
        int col_new;
        int ret = INT_MAX;
        for(int i = 0; i < 3; ++i) {
            col_new = c + nxt[i];
            if( col_new < 0 || col_new == n )
                continue;
            ret = min(ret,matrix[r][c]+rec(matrix,n,r+1,col_new));
        }

        return mem[r][c] = ret;
    }



public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(); // n == matrix.length == matrix[i].length

        memset(mem,-1,sizeof mem);

        int ans = INT_MAX;
        for(int i = 0; i < n; ++i)
            ans = min(ans,rec(matrix,n,0,i));

        return ans;
    }
};
