
// 3030. Find the Grid of Region Average
// https://leetcode.com/problems/find-the-grid-of-region-average/






class Solution {
private:
    void eval_regions(vector<vector<int>>& image, int m, int n, int threshold, vector<vector<bool>>& is_region_valid) {
        for(int i = 0; i < m-2; ++i) {
            for(int j = 0; j < n-2; ++j) {

                if( abs(image[i][j] - image[i][j+1])       > threshold ||     // row 0 of region right
                    abs(image[i][j] - image[i+1][j])       > threshold ||     //                 down
                    abs(image[i][j+1] - image[i][j+2])     > threshold ||     //                 right
                    abs(image[i][j+1] - image[i+1][j+1])   > threshold ||     //                 down
                    abs(image[i][j+2] - image[i+1][j+2])   > threshold ||     //                 down
                    abs(image[i+1][j] - image[i+1][j+1])   > threshold ||     // row 1 of region right
                    abs(image[i+1][j] - image[i+2][j])     > threshold ||     //                 down
                    abs(image[i+1][j+1] - image[i+1][j+2]) > threshold ||     //                 right
                    abs(image[i+1][j+1] - image[i+2][j+1]) > threshold ||     //                 down
                    abs(image[i+1][j+2] - image[i+2][j+2]) > threshold ||     //                 down
                    abs(image[i+2][j] - image[i+2][j+1])   > threshold ||     // row 2 of region right
                    abs(image[i+2][j+1] - image[i+2][j+2]) > threshold ) {    //                 right

                    is_region_valid[i][j] = false;
                    continue;
                }

            }
        }
        return;
    }

public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        int m = image.size();
        int n = image[0].size();

        // brute force

        int ps[m+1][n+1];memset(ps,0,sizeof ps); // 2D prefix sum
        for(int i = 1; i <= m; ++i)
            for(int j = 1; j <= n; ++j)
                ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + image[i-1][j-1];

        vector<vector<bool>> is_region_valid(m-2,vector<bool>(n-2,true));
        eval_regions(image,m,n,threshold,is_region_valid);

        vector<vector<int>> ans(m,vector<int>(n));
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {

                // which regions does the current cell belong to?
                int region_count = 0;
                int regions_averages_sum = 0;

                for(int rd = -2; rd <= 0; ++rd) {
                    int i_new = i + rd;
                    if( i_new < 0 || i_new > m-3 )
                        continue;
                    for(int cd = -2; cd <= 0; ++cd) {
                        int j_new = j + cd;
                        if( j_new < 0 || j_new > n-3 )
                            continue;

                        // printf("i %i j %i belong to region %i %i\n", i, j, i_new, j_new);

                        if( is_region_valid[i_new][j_new] ) {
                            // get the regions sum
                            int region_sum = ps[i_new+2+1][j_new+2+1] - ps[i_new+2+1][j_new+2-2] - ps[i_new+2-2][j_new+2+1] + ps[i_new+2-2][j_new+2-2];
                            // average of the region (rounded down to the nearest integer)
                            int region_avg = region_sum / 9;

                            ++region_count;
                            regions_averages_sum += region_avg;
                        }
                    }
                }
                if( region_count == 0 ) {
                    ans[i][j] = image[i][j];
                } else {
                    ans[i][j] = regions_averages_sum / region_count;
                }
            }
        }

        return ans;
    }
};
