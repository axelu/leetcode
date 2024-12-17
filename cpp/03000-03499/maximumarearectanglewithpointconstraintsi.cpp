
// 3380. Maximum Area Rectangle With Point Constraints I
// https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/






class Solution {
private:
    int area(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
        // 0 bottom left
        // 1 top left
        // 2 bottom right
        // 3 top right

        // return -1 if the points don't make a rectangle

        if( x0 != x1 || x2 != x3 || y0 != y2 || y1 != y3 )
            return -1;

        int l = x2 - x1;
        int h = y1 - y0;

        return l * h;
    }

public:
    int maxRectangleArea(vector<vector<int>>& points) {
        int n = points.size(); // 1 <= n <= 10
        // worst case 𝐶(𝑛,𝑟) -> C(10,4) = 210
        // we would try all possible combinations of 4 out of 10 points,
        // because small constraint -> brute force

        if( n < 4 )
            return -1;

        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        if( n == 4 ) {
            return area(points[0][0], points[0][1],
                        points[1][0], points[1][1],
                        points[2][0], points[2][1],
                        points[3][0], points[3][1]);
        }

        int ans = -1;

        for(int i = 0; i < n-3; ++i) {
            int x0 = points[i][0];
            int y0 = points[i][1];
            for(int j = i+1; j < n-2; ++j) {
                int x1 = points[j][0];
                int y1 = points[j][1];
                for(int k = j+1; k < n-1; ++k) {
                    int x2 = points[k][0];
                    int y2 = points[k][1];
                    for(int o = k+1; o < n; ++o) {
                        int x3 = points[o][0];
                        int y3 = points[o][1];
                        int a = area(x0, y0, x1, y1, x2, y2, x3, y3);
                        if( a != -1 ) {
                            // is there another point other than i, j, k, o
                            // that is inside or on the border of our rectangle?

                            bool is_valid = true;
                            for(int m = 0; m < n; ++m) {
                                if( m == i || m == j || m == k || m == o )
                                    continue;

                                int xm = points[m][0];
                                int ym = points[m][1];

                                if( y0 <= ym && ym <= y1 && x0 <= xm && xm <= x2 ) {
                                    is_valid = false;
                                    break;
                                }
                            }
                            if( is_valid && a > ans )
                                ans = a;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
