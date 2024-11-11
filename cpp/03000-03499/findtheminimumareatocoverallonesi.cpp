
// 3195. Find the Minimum Area to Cover All Ones I
// https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/



class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int m = grid.size();    // rows
        int n = grid[0].size(); // cols

        int imn = m-1;
        int imx = 0;
        int jmn = n-1;
        int jmx = 0;

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 1 ) {
                    imn = min(imn, i);
                    imx = max(imx, i);
                    jmn = min(jmn, j);
                    jmx = max(jmx, j);
                }
            }
        }

        int w = jmx - jmn + 1;
        int h = imx - imn + 1;

        return w * h;
    }
};
