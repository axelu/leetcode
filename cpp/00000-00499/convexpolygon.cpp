
// 469. Convex Polygon
// https://leetcode.com/problems/convex-polygon/





class Solution {
private:
    // convex polygon
    // Graham scan
    // for three points p(p0,p1), q(q0,q1) and r(r0,r1)
    // compute the z-coordinate of the cross product
    // of the two vectors p->q and p->r
    // if 0 the points are collinear
    // if > 0 then left turn or counter-clockwise orientation
    // if < 0 then right turn or clockwise orientation
    int orientation(vector<int>& p, vector<int>& q, vector<int>& r) {
        return (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    }

public:
    bool isConvex(vector<vector<int>>& points) {
        int n = points.size();

        if( n < 4 )
            return true;

        // shift to positive plane
        for(int i = 0; i < n; ++i) {
            points[i][0] += 10000;
            points[i][1] += 10000;
        }

        // determine the 'orientation'
        int direction = 0;

        int p = 0;
        int q = 1;
        int r = 1;
        while( direction == 0  && r < n-1 ) {
            ++r;
            direction = orientation(points[p],points[q],points[r]);
        }
        // edge case
        if( direction == 0 )
            return true;

        // cout << "direction " << direction << endl;

        for(int p = 0, q = 1, r = 2; p < n; ++p, ++q, ++r) {
            q = q % n;
            r = r % n;
            int v = orientation(points[p],points[q],points[r]);
            // cout << p << " " << q << " " << r << " v " << v << endl;
            if( v == 0 )
                continue;
            if( direction < 0 && v > 0 || direction > 0 && v < 0 )
                return false;
        }

        return true;
    }
};
