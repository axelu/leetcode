
// 1620. Coordinate With Maximum Network Quality
// https://leetcode.com/problems/coordinate-with-maximum-network-quality/



class Solution {
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        auto n = towers.size();

        // determine plane xmin,xmax,ymin,ymax
        int xmin = 51, xmax = -1, ymin = 51, ymax = -1, qfmax = 0;
        for(int i = 0; i < n; ++i) {
            xmin = min(xmin,towers[i][0]);
            xmax = max(xmax,towers[i][0]);
            ymin = min(ymin,towers[i][1]);
            ymax = max(ymax,towers[i][1]);
            qfmax = max(qfmax,towers[i][2]);
        }
        if( qfmax == 0 ) return {0,0};

        vector<int> r = {51,51};
        int xd,yd,q;
        int qmax = 0;
        double d;
        for(int x = xmin; x <= xmax; ++x) {
            for(int y = ymin; y <= ymax; ++y) {
                q = 0;
                for(int i = 0; i < n; ++i) {
                   xd = abs(x-towers[i][0]);
                   yd = abs(y-towers[i][1]);
                   d = sqrt(xd*xd+yd*yd);
                   if( (double)radius - d >= 0.0  )
                       q += (double)towers[i][2] / (1.0 + d);
                }
                if( q > qmax ) {
                    qmax = q;
                    r = {x,y};
                } else if( q = qmax ) {
                    if( x < r[0] || ( x == r[0] && y < r[1] ))
                        r = {x,y};
                }
            }
        }

        return r;
    }
};
