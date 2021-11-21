
// 1924. Erect the Fence II
// https://leetcode.com/problems/erect-the-fence-ii/





// smallest-circle problem, minimum covering circle problem,
// bounding circle problem, smallest enclosing circle problem
// https://en.wikipedia.org/wiki/Smallest-circle_problem

class Solution {
private:
    // Euclidean distance between two points
    double dist(double x1, double y1, double x2, double y2) {
        // √((x₂ - x₁)² + (y₂ - y₁)²)
        return sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
    }

    vector<double> get_circle_center(double bx, double by,
                                     double cx, double cy) {
        double B = bx * bx + by * by;
        double C = cx * cx + cy * cy;
        double D = bx * cy - by * cx;
        return {(cy * B - by * C) / (2 * D),
                (bx * C - cx * B) / (2 * D) };
    }

    // return a unique circle that intersects 3 points
    vector<double> circle_from(double ax, double ay,
                               double bx, double by,
                               double cx, double cy) {

        vector<double> C = get_circle_center(bx-ax,by-ay,cx-ax,cy-ay);

        C[0] += ax;
        C[1] += ay;
        return {C[0],C[1],dist(C[0],C[1],ax,ay)};
    }

    // return the smallest circle that intersects 2 points
    vector<double> circle_from(double ax, double ay,
                               double bx, double by) {

        double cx = (ax+bx)/2.0;
        double cy = (ay+by)/2.0;
        return {cx,cy,dist(ax,ay,bx,by)/ 2.0};
    }

    bool is_inside(vector<double>& C, vector<int>& P) {
        return dist(C[0],C[1],P[0],P[1]) <= C[2];
    }


    // check if circle encloses points
    bool is_valid_circle(vector<double>& C, vector<vector<int>>& points) {

        for(int i = 0; i < points.size(); ++i)
            if( !is_inside(C,points[i]) )
                return false;

        return true;
    }

    // return the minimum enclosing circle for n <= 3
    vector<double> min_circle_trivial(vector<vector<int>>& points) {
        int n = points.size();
        double ax,ay,bx,by,cx,cy;

        if( n == 0 )
            return {0.0,0.0,0.0};
        else if( n == 1)
            return {(double)points[0][0],(double)points[0][1],0.0};
        else if( n == 2 ) {
            ax = points[0][0];
            ay = points[0][1];
            bx = points[1][0];
            by = points[1][1];
            return circle_from(ax,ay,bx,by);
        }

        // check if enclosing circle can be determined by 2 points only
        vector<double> C;
        for(int i = 0; i < 3; ++i)
            for(int j = i + 1; j < 3; ++j) {
                ax = points[i][0];
                ay = points[i][1];
                bx = points[j][0];
                by = points[j][1];
                C = circle_from(ax,ay,bx,by);
                if( is_valid_circle(C,points))
                    return C;
            }

        ax = points[0][0];
        ay = points[0][1];
        bx = points[1][0];
        by = points[1][1];
        cx = points[2][0];
        cy = points[2][1];
        return circle_from(ax,ay,bx,by,cx,cy);
    }

    // Welzl's algorithm
    // takes a set of input points P and
    // a set R points on the circle boundary.
    vector<double> welzl_helper(vector<vector<int>>& P,
                                 vector<vector<int>> R, int n) {

        // n represents the number of points in P
        // that are not yet processed.

        if( n == 0 || R.size() == 3 )
            return min_circle_trivial(R);


        // pick a random point randomly
        int idx = rand() % n;
        vector<int> p = P[idx];

        // put the picked point at the end of P
        // since it's more efficient than
        // deleting from the middle of the vector
        swap(P[idx],P[n-1]);

        // get the minimum enclosing circle d from the
        // set of points P - {p}
        vector<double> D = welzl_helper(P,R,n-1);

        // if d contains p, return d
        if( is_inside(D,p))
            return D;

        // else, must be on the boundary of the minimum enclosing circle
        R.push_back(p);

        // return the minimum enclosing circle for P - {p} and R U {p}
        // U = union of two sets
        return welzl_helper(P,R,n-1);
    }


    vector<double> welzl(vector<vector<int>>& points) {
        //vector<vector<int>> P = points;
        random_shuffle(points.begin(),points.end());
        return welzl_helper(points,{},points.size());
    }

public:
    vector<double> outerTrees(vector<vector<int>>& trees) {
        // 1 <= trees.size() <= 3000

        if( trees.size() <= 3 )
            return min_circle_trivial(trees);

        srand(time(nullptr)); // use current time as seed for random generator
        return welzl(trees);
    }
};
