
// 1453. Maximum Number of Darts Inside of a Circular Dartboard
// https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/





/* in the case of two circles
 * to get to xc and yc for one of the circles
 * r2 = (x1-xc)(x1-xc) + (yc-y1)(yc-y1)
 * r2 = (yc-y2)(yc-y2) + (x2-xc)(x2-xc)
 *      --------------   --------------
 * the underlined parts must be identical in both equations
 * hence we can resolve as follows
 * r2 = (x1-xc)(x1-xc) + (x2-xc)(x2-xc) and
 * r2 = (yc-y2)(yc-y2) + (yc-y1)(yc-y1)

 * see https://web.archive.org/web/20180128170023/http://mathforum.org/library/drmath/view/53027.html

 */
class Solution {
private:
    double dist2(double x1, double y1, double x2, double y2) {
        double a2 = (x2-x1)*(x2-x1);
        double b2 = (y2-y1)*(y2-y1);
        double c2 = a2 + b2;
        return c2;
    }

    int cnt(vector<vector<int>>& darts, int n, int i, int j, int r2, double x, double y, int offset) {
        int ret = 0;
        for(int k = 0; k < n; ++k) {
            if( k == i || k == j )
                continue;
            double dst2 = dist2(x,y,darts[k][0]+offset,darts[k][1]+offset);
            if( dst2 <= r2 ) // TODO floating point compare
                ++ret;
        }
        return ret;
    }

public:
    int numPoints(vector<vector<int>>& darts, int r) {
        int n = darts.size();
        if( n == 1 )
            return 1;

        int r2 = r * r;
        int d  = 2 * r;
        int d2 = d * d;

        int ans = 1; // we will always be able to include 1 point

        int offset = 0; // 20000
        for(int i = 0; i < n-1; ++i) {
            int x1 = darts[i][0] + offset;
            int y1 = darts[i][1] + offset;
            for(int j = i+1; j < n; ++j) {
                int x2 = darts[j][0] + offset;
                int y2 = darts[j][1] + offset;
                // cout << "checking pair [" << x1 << "," << y1 << "],[" << x2 << "," << y2 << "]" << endl;

                int c2 = dist2(x1,y1,x2,y2);
                // cout << "distance square " << c2 << endl;
                if( c2 > d2 ) {
                    // no circle
                    continue;

                } else if( c2 == d2 ) {
                    // 1 circle
                    // center of our circle [x,y] lies on the line
                    // that connects [x1,y1] and [x2,y2]
                    double x = (x1+x2)/2.0;
                    double y = (y1+y2)/2.0;
                    // cout << "1 circle x " << x << " y " << y << endl;
                    ans = max(ans, 2 + cnt(darts,n,i,j,r2,x,y,offset));

                } else {
                    // 2 circles
                    // let [x3,y3] be the point halfway between [x1,y1] and [x2,y2]
                    double x3 = (x1+x2)/2.0;
                    double y3 = (y1+y2)/2.0;
                    // distance between points [x1,y1] and [x2,y2]
                    double q = sqrt(c2);

                    double x = x3 + sqrt(r2 - (q/2)*(q/2)) * (y1-y2)/q;
                    double y = y3 + sqrt(r2 - (q/2)*(q/2)) * (x2-x1)/q;
                    // cout << "2 circle       x " << x << " y " << y << endl;
                    ans = max(ans, 2 + cnt(darts,n,i,j,r2,x,y,offset));

                    x = x3 - sqrt(r2 - (q/2)*(q/2)) * (y1-y2)/q;
                    y = y3 - sqrt(r2 - (q/2)*(q/2)) * (x2-x1)/q;
                    // cout << "2 circle still x " << x << " y " << y << endl;
                    ans = max(ans, 2 + cnt(darts,n,i,j,r2,x,y,offset));
                }
            }
        }

        return ans;
    }
};
