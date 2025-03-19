
// 3417. Zigzag Grid Traversal With Skip
// https://leetcode.com/problems/zigzag-grid-traversal-with-skip/



class Solution {
public:
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        vector<int> ans;

        bool take = true;
        bool fwd = true;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                int real_j = fwd ? j : (n-1) - j;
                if( take ) {
                    ans.push_back(grid[i][real_j]);
                }
                take = !take;
            }
            fwd = !fwd;
        }

        return ans;
    }
};
