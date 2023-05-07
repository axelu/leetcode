
// 963. Minimum Area Rectangle II
// https://leetcode.com/problems/minimum-area-rectangle-ii/



class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();  // 1 <= points.length <= 50
        if( n < 4 )             // need min 4 points to make a rectangle
            return 0;

        // calculate distances between all points
        long d2[n][n];  // (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)
                        // min x,y 0; max x,y 40000; => max 3200000000, hence long

        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                long x1 = points[i][0];
                long y1 = points[i][1];
                long x2 = points[j][0];
                long y2 = points[j][1];
                d2[i][j] = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
                d2[j][i] = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
                // cout << "distance sqare " << i << " " << j << " " << d2[i][j] << endl;
            }
        }

        double mn_area = 1600000001;

        for(int p1 = 0; p1 < n; ++p1) {                     // point 1
            // cout << "p1 " << p1 << endl;

            for(int p2 = 0; p2 < n; ++p2) {                 // point 2
                if( p2 == p1 )
                    continue;

                long d2_p1p2 = d2[p1][p2];
                // cout << "    p2 " << p2 << " d2_p1p2 " << d2_p1p2 << endl;

                for(int p3 = 0; p3 < n; ++p3) {             // point 3
                    if( p3 == p1 || p3 == p2 )
                        continue;

                    // determine if there is a point perpendicular
                    // to the line that p1 p2 forms

                    long d2_p1p3 = d2[p1][p3];
                    long d2_p2p3 = d2[p2][p3];
                    // cout << "        p3 " << p3 << " d2_p1p3 " << d2_p1p3 << " d2_p2p3 " << d2_p2p3 << endl;

                    // Pythagorean theorem a*a + b*b = c*c
                    if( d2_p1p2 + d2_p1p3 == d2_p2p3 ) {

                        for(int p4 = 0; p4 < n; ++p4) {  // point 4
                            if( p4 == p1 || p4 == p2 || p4 == p3 )
                                continue;

                            // now we need a 4th point
                            // cout << "            p4 " << p4 << endl;

                            long d2_p1p4 = d2[p1][p4];
                            long d2_p2p4 = d2[p2][p4];
                            long d2_p3p4 = d2[p3][p4];

                            if( d2_p2p4 == d2_p1p3 && d2_p3p4 == d2_p1p2 && d2_p2p3 == d2_p1p4 ) {
                                // we have a rectangle
                                // cout << "we have a rectangle" << endl;

                                double t = sqrt(d2_p1p2) * sqrt(d2_p1p3);
                                mn_area = min(mn_area,t);
                            }
                        }
                    }
                }
            }
        }

        return mn_area == 1600000001 ? 0 : mn_area;
    }
};
