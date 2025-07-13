
// 3546. Equal Sum Grid Partition I
// https://leetcode.com/problems/equal-sum-grid-partition-i/




class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        long long row_sum[100000];memset(row_sum, 0, sizeof row_sum);
        long long col_sum[100000];memset(col_sum, 0 ,sizeof col_sum);
        for(int i = 0; i < m; ++i) {     // row
            for(int j = 0; j < n; ++j) { // col
                row_sum[i] += (long long)grid[i][j];
                col_sum[j] += (long long)grid[i][j];
            }
        }

        // split horizontally
        long long row_prefixSum[100001];
        row_prefixSum[0] = 0LL;
        for(int i = 1; i <= m; ++i)
            row_prefixSum[i] = row_prefixSum[i-1] + row_sum[i-1];
        for(int i = 1; i < m; ++i)
            if( row_prefixSum[i] == row_prefixSum[m] - row_prefixSum[i] )
                return true;

        // split vertically
        long long col_prefixSum[100001];
        col_prefixSum[0] = 0LL;
        for(int j = 1; j <= n; ++j)
            col_prefixSum[j] = col_prefixSum[j-1] + col_sum[j-1];
        for(int j = 1; j < n; ++j)
            if( col_prefixSum[j] == col_prefixSum[n] - col_prefixSum[j] )
                return true;

        return false;
    }
};
