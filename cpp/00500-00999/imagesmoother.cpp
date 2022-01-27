
// 661. Image Smoother
// https://leetcode.com/problems/image-smoother/



class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int m = M.size();    // rows
        int n = M[0].size(); // cols

        vector<vector<int>> ans(m,vector<int>(n,0));

        // directions
        // east,south-east,south,south-west,west,north-west,north,north-east
        int dirR[] = {0, 1, 1, 1, 0,-1,-1,-1};
        int dirC[] = {1, 1, 0,-1,-1,-1, 0, 1};

        int sum,cnt;
        int r,c;
        for(int i = 0; i < m; ++i) { // row
            for(int j = 0; j < n; ++j) { // col
                sum = M[i][j];
                cnt = 1;
                // explore all eight directions
                for(int k = 0; k < 8; ++k) {
                    r = i + dirR[k];
                    if( r < 0 || r >= m ) continue;
                    c = j + dirC[k];
                    if( c < 0 || c >= n ) continue;

                    sum += M[r][c];
                    ++cnt;
                }
                ans[i][j] = sum/cnt;
            }
        }
        return ans;
    }
};
