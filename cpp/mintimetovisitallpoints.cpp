
// 1266. Minimum Time Visiting All Points
// https://leetcode.com/problems/minimum-time-visiting-all-points/


class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        auto n = points.size();
        if( n <= 1 ) return 0;

        int r = 0;
        int x = points[0][0];
        int y = points[0][1];
        int xi, yi;
        for(int i = 1; i < n; ++i) {
            xi = points[i][0];
            yi = points[i][1];
            while(x != xi || y != yi) {
                ++r;
                if( x != xi )
                    x = x < xi ? ++x : --x;
                if( y != yi )
                    y = y < yi ? ++y : --y;
            }
        }

        return r;
    }
};
