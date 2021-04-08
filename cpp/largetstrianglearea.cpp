
// 812. Largest Triangle Area
// https://leetcode.com/problems/largest-triangle-area/


class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        size_t n = points.size();
        // combination with 3 out of 50 where order does not matter
        // 19600 combinations worst case, so brute force is ok

        double ans = 0.000000, area;
        int x1,y1,x2,y2,x3,y3;
        for(int i = 0; i < n-2; ++i) {
            x1 = points[i][0];
            y1 = points[i][1];
            for(int j = i+1; j < n-1; ++j) {
                x2 = points[j][0];
                y2 = points[j][1];
                for(int k = j+1; k < n; ++k) {
                    x3 = points[k][0];
                    y3 = points[k][1];
                    // Shoelace Formula by Albrecht Ludwig Friedrich Meister in 1769
                    area = 0.5000000 * abs(x1*y2 - x2*y1   +   x2*y3 - x3*y2   +   x3*y1 - x1*y3);
                    if( area - ans > 1e-6 ) ans = area;
                }
            }
        }

        return ans;
    }
};
