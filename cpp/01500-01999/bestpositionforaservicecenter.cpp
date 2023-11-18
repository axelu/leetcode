
// 1515. Best Position for a Service Centre
// https://leetcode.com/problems/best-position-for-a-service-centre/






/* see
 * https://en.wikipedia.org/wiki/Geometric_median
 *     Weizsfeld algorithm could be used, but opting for
 *     https://en.wikipedia.org/wiki/Simulated_annealing
 *     https://stackoverflow.com/questions/12934213/how-to-find-out-geometric-median
 */
class Solution {
private:
    // Euclidean distance between two points
    double dist(double x1, double y1, double x2, double y2) {
        // √((x₂ - x₁)² + (y₂ - y₁)²)
        return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
    }

    double solve(vector<vector<int>>& positions, double x, double y) {
        // return sum of the euclidean distances of all positions to [x,y]
        double ret = 0.0;
        for(auto& v: positions)
            ret += dist(x,y,v[0],v[1]);
        return ret;
    }

public:
    double getMinDistSum(vector<vector<int>>& positions) {
        const int n = positions.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return dist(positions[0][0],positions[0][1],positions[1][0],positions[1][1]);

        // per constraint our grid is 0 <= xi, yi <= 100, so we will start in the middle
        double x = 50;
        double y = 50;
        double ans = solve(positions,x,y);

        double increment = 10.0;    // initial increment
        const double precision = 0.000001;

        // directions   R  D  L  U
        const int dirR[4] = { 0, 1, 0,-1};
        const int dirC[4] = { 1, 0,-1, 0};

        while( increment > precision ) {
            bool f = false;
            for(int k = 0; k < 4; ++k) {
                double x_new = x + increment * dirR[k]; // TODO check if inside grid
                double y_new = y + increment * dirC[k]; // TODO check if inside grid

                double t = solve(positions,x_new,y_new);
                if( t < ans ) {
                    // we got a better answer
                    ans = t;
                    x = x_new;
                    y = y_new;
                    f = true;
                    break;
                }
            }
            // increase our precision by decreasing our increment,
            // because with the current increment we did not find a better point
            if( !f )
                increment /= 10;
        }

        return ans;
    }
};
