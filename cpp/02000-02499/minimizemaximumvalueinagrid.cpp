
// 2371. Minimize Maximum Value in a Grid
// https://leetcode.com/problems/minimize-maximum-value-in-a-grid/




class Solution {
public:
    vector<vector<int>> minScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> ans(m,vector<int>(n));
        // truths
        //    within a row a given cell needs to retain its order (no dups in a row)
        //    within a col a given cell needs to retain its order (no dups in a col)
        //    within a connect component (cc) that is increasing, each cell needs to
        //        retain is order to its neighbors in said cc

        // initially the grid has distinct positive integers
        int idx = 0;
        vector<vector<int>> v(m*n); // val,i,j
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                v[idx++] = {grid[i][j],i,j};
            }
        }
        sort(v.begin(),v.end(),[](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0];
        });

        int row_mx[m];memset(row_mx,0,sizeof row_mx);
        int col_mx[n];memset(col_mx,0,sizeof col_mx);
        for(auto& t: v) {
            int i = t[1];
            int j = t[2];
            // cout << "i " << i << " j " << j << " grid[i][j] " << grid[i][j] << endl;
            int mx = max(row_mx[i],col_mx[j]);
            ans[i][j] = mx+1;
            row_mx[i] = mx+1;
            col_mx[j] = mx+1;
        }

        return ans;
    }
};
