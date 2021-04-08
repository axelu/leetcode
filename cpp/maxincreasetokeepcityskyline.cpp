
// 807. Max Increase to Keep City Skyline
// https://leetcode.com/problems/max-increase-to-keep-city-skyline/



class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        // top bottom -> max per col
        int tb[n]; memset(tb,0,sizeof tb);
        // left right -> max per row
        int lr[m];

        int mxlr,i,j;
        for(i = 0; i < m; ++i) {     // row
            mxlr = 0;
            for(j = 0; j < n; ++j) { // col
                tb[j] = max(tb[j],grid[i][j]);
                mxlr = max(mxlr,grid[i][j]);
            }
            lr[i] = mxlr;
        }

        /*
        cout << "top bottom" << endl;
        for(j = 0; j < n; ++j) cout << tb[j] << " ";
        cout << endl;
        cout << "left right" << endl;
        for(i = 0; i < m; ++i) cout << lr[i] << " ";
        cout << endl;
        */

        int ans = 0;
        for(i = 0; i < m; ++i) {     // row
            for(j = 0; j < n; ++j) { // col
                ans += min(tb[j],lr[i]) - grid[i][j];
            }
        }

        return ans;
    }
};
