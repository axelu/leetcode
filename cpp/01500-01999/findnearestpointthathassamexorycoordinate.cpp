
// 1779. Find Nearest Point That Has the Same X or Y Coordinate
// https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/



class Solution {
public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int n = points.size();

        int idx = -1;
        int ans = INT_MAX;
        int md;
        for(int i = 0; i < n; ++i) {
            if( points[i][0] == x || points[i][1] == y ) {
                md = abs(x-points[i][0])+abs(y-points[i][1]);
                if( md < ans ) {
                    ans = md;
                    idx = i;
                }
            }
        }
        return idx;
    }
};
