
// 939. Minimum Area Rectangle
// https://leetcode.com/problems/minimum-area-rectangle/


class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int n = points.size();
        if( n < 4 )
            return 0;

        sort(points.begin(),points.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        map<int,set<int>> xy;
        map<int,set<int>> yx;
        for(auto v: points) {
            int x = v[0];
            int y = v[1];
            xy[x].insert(y);
            yx[y].insert(x);
        }

        int mn_area = 1600000001;

        for(int p1 = 0; p1 < n-3; ++p1) {
            int x1 = points[p1][0];
            int y1 = points[p1][1];

            // is there a point on the same y-axis as p1? -> same x coordinate as p1
            for(auto f2 = xy[x1].upper_bound(y1); f2 != xy[x1].end(); ++f2) {
                // we have a second point
                int x2 = x1;
                int y2 = *f2;

                // is there a point on the same x-axis as p1? -> same y coordinate as p1
                for(auto f3 = yx[y1].upper_bound(x1); f3 != yx[y1].end(); ++f3) {
                    // we have a third point
                    int x3 = *f3;
                    int y3 = y1;

                    // if we would find a 4th point, we would get a rectangle with area
                    int area = (y2-y1) * (x3-x1);
                    if( area < mn_area && xy[x3].find(y2) != xy[x3].end() )
                        mn_area = area;
                }
            }
        }

        return mn_area == 1600000001 ? 0 : mn_area;
    }
};
