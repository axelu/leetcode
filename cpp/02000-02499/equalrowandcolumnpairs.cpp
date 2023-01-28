
// 2352. Equal Row and Column Pairs
// https://leetcode.com/problems/equal-row-and-column-pairs/





class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size(); // n x n grid, 1 <= n <= 200

        // brute force

        int ans = 0;

        for(int i = 0; i < n; ++i) {
            // initially all columns are candidates
            vector<int> candidates(n);
            for(int k = 0; k < n; ++k)
                candidates[k] = k;

            for(int j = 0; j < n; ++j) {
                int val = grid[i][j];

                // check remaining candidates
                for(auto it = candidates.begin(); it != candidates.end(); ) {
                    if( grid[j][*it] != val )
                        candidates.erase(it);
                    else
                        ++it;
                }
            }

            ans += candidates.size();
        }

        return ans;
    }
};
