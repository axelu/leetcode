
// 3070. Count Submatrices with Top-Left Element and Sum Less Than k
// https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/




class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        // brute force

        int ans = 0;

        long ps[m+1][n+1];memset(ps,0,sizeof ps); // 2D prefix sum
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j) {
                ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + (long)grid[i-1][j-1];
                if( ps[i][j] <= (long)k )
                    ++ans;
                else
                    break;
            }


        return ans;
    }
};
