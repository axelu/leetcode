
// 2711. Difference of Number of Distinct Values on Diagonals
// https://leetcode.com/problems/difference-of-number-of-distinct-values-on-diagonals/





class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m = grid.size();     // rows
        int n = grid[0].size();  // cols

        vector<vector<int>> ans(m,vector<int>(n));

        // diagonals starting in row 0
        for(int k = 0; k < n; ++k) {
            int unique[51];memset(unique,0,sizeof unique);
            vector<int> prefixSum = {0};
            int i = 0;
            int j = k;
            while( i < m && j < n ) {
                ++unique[grid[i][j]];
                if( unique[grid[i][j]] == 1 )
                    prefixSum.push_back(prefixSum.back()+1);
                else
                    prefixSum.push_back(prefixSum.back());
                ++i;
                ++j;
            }

            memset(unique,0,sizeof unique);
            vector<int> suffixSum = {0};
            --i;
            --j;
            while( i >= 0 ) {
                ++unique[grid[i][j]];
                if( unique[grid[i][j]] == 1 )
                    suffixSum.push_back(suffixSum.back()+1);
                else
                    suffixSum.push_back(suffixSum.back());
                --i;
                --j;
            }

            ++i;
            ++j;
            int pf_idx = 0;
            int sf_idx = suffixSum.size() - 2; // prefixSum.size() == suffixSum.size();
            while( i < m && j < n ) {
                int t = abs( prefixSum[pf_idx] - suffixSum[sf_idx]);
                ans[i][j] = t;
                ++pf_idx;
                --sf_idx;
                ++i;
                ++j;
            }
        }

        // diagonals starting in col 0 and row > 0
        for(int k = 1; k < m; ++k) {
            int unique[51];memset(unique,0,sizeof unique);
            vector<int> prefixSum = {0};
            int i = k;
            int j = 0;
            while( i < m && j < n ) {
                ++unique[grid[i][j]];
                if( unique[grid[i][j]] == 1 )
                    prefixSum.push_back(prefixSum.back()+1);
                else
                    prefixSum.push_back(prefixSum.back());
                ++i;
                ++j;
            }

            memset(unique,0,sizeof unique);
            vector<int> suffixSum = {0};
            --i;
            --j;
            while( j >= 0 ) {
                ++unique[grid[i][j]];
                if( unique[grid[i][j]] == 1 )
                    suffixSum.push_back(suffixSum.back()+1);
                else
                    suffixSum.push_back(suffixSum.back());
                --i;
                --j;
            }

            ++i;
            ++j;
            int pf_idx = 0;
            int sf_idx = suffixSum.size() - 2; // prefixSum.size() == suffixSum.size();
            while( i < m && j < n ) {
                int t = abs( prefixSum[pf_idx] - suffixSum[sf_idx]);
                ans[i][j] = t;
                ++pf_idx;
                --sf_idx;
                ++i;
                ++j;
            }
        }

        return ans;
    }
};
