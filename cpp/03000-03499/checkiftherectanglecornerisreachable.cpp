
// 3235. Check if the Rectangle Corner Is Reachable
// https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/




/*     3  |  2
 * -------|----
 * |      |
 * |   0  |  1
 * |      |
 * --------
 *
 * circle path from 2 to 3 (or vice versa) cannot create a barrier
 * circle path from 1 to 2 (or vice versa) cannot create a barrier
 * circle path from 1 to 3 (or vice versa) could
 */
class Solution {
private:
    long xCorner;
    long yCorner;
    vector<vector<int>>* circles;
    int c_sz;
    int cl[1000];   // circle location in quadrant as shown above
    int cm[1000];   // mask bits from right to left 0 crosses_bottom_edge 1 crosses_left_edge 2 crosses_top_edge 3 crosses_right_edge
    int seen[1000];
    bool is_blocked;

    int get_mask(long x, long y, long r) {
        long x_min = x - r;
        long x_max = x + r;
        long y_min = y - r;
        long y_max = y + r;
        // bit                    3               2                   1               0
        int mask = 0; // crosses_right_edge  crosses_top_edge  crosses_left_edge  crosses_bottom_edge

        //bool crosses_bottom_edge = false;
        //bool crosses_left_edge   = false;
        //bool crosses_top_edge    = false;
        //bool crosses_right_edge  = false;
        if( y <= yCorner && x_min <= 0 )
            mask |= (1<<1); // crosses_left_edge = true;
        if( y <= yCorner && x < xCorner && x_max >= xCorner ) // from inside
            mask |= (1<<3); // crosses_right_edge = true;
        if( y <= yCorner && x > xCorner && x_min < xCorner )  // from outside
            mask |= (1<<3); // crosses_right_edge = true;
        if( x <= xCorner && y_min <= 0 )
            mask |= 1; // crosses_bottom_edge = true;
        if( x <= xCorner && y < yCorner && y_max >= yCorner ) // from inside
            mask |= (1<<2); // crosses_top_edge = true;
        if( x <= xCorner && y > yCorner && y_min < yCorner )  // from outside
            mask |= (1<<2); // crosses_top_edge = true;


        return mask;
    }

    // Euclidean distance between two points, returns the square of it
    long dist2(long x1, long y1, long x2, long y2) {
        // ((x₂ - x₁)² + (y₂ - y₁)²)
        return ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
    }

    bool block(long x1, long y1, long x3, long y3) {
        // cout << "block x1 " << x1 << " y1 " << y1 << " x3 " << x3 << " y3 " << y3 << endl;

        // let 1 be our point in quadrant 1
        // let 3 be our point in quadrant 3
        // let 2 be our point y1, xCorner
        // let 4 be our point yCorner, xCorner

        // vector A p1 -> p2
        // vector B p1 -> p4
        // vector C p1 -> p3

        // if the angle between A B < angle A C then block

        long x4 = xCorner;
        long y4 = yCorner;

        // calc angle counterclockwise from east to point pivoting on location

        long a = y4 - y1;
        long b = x4 - x1;

        double pi = 3.14159265;
        double deg1 = atan2(a, b) * 180 / pi;
        if( deg1 < 0 )
            deg1 += 360;

        // cout << deg1 << endl;

        a = y3 - y1;
        b = x3 - x1;
        double deg2 = atan2(a, b) * 180 / pi;
        if( deg2 < 0 )
            deg2 += 360;

        // cout << deg2 << endl;

        return deg2 > deg1;
    }

    /*
    bool block(long x, long y, long r) {
        // cout << "block x " << x << " y " << y << " r " << r << endl;

        // the point x,y is in quadrant 1

        // c² = a² + b²  -->  b² = c² - a²
        // let a = x - xCorner
        // let c = r

        long a = x - xCorner;
        long c = r;
        long b2 = (c*c) - (a*a);

        // if b2 < (yCorner - y)*(yConrer - y) the circles block

        return b2 < (yCorner - y)*(yCorner - y);
    }
    */

    int dfs(int i, int comp, bool& crosses_bottom_edge, bool& crosses_left_edge, bool& crosses_top_edge, bool& crosses_right_edge) {
        // cout << "dfs " << i << " comp " << comp << endl;

        seen[i] = comp;

        int ret = 1; // counting size of component

        long xi   = circles->at(i)[0];
        long yi   = circles->at(i)[1];
        long ri   = circles->at(i)[2];
        int cli   = cl[i];
        crosses_bottom_edge = crosses_bottom_edge || cm[i] & 1;
        crosses_left_edge   = crosses_left_edge || cm[i] & (1<<1);
        crosses_top_edge    = crosses_top_edge || cm[i] & (1<<2);
        crosses_right_edge  = crosses_right_edge || cm[i] & (1<<3);

        for(int j = 0; j < c_sz; ++j) {
            if( j == i )
                continue;
            if( seen[j] != -1 )
                continue;

            int clj = cl[j];
            if( clj == 2 )
                continue;
            int cmj = cm[j];
            if( (cl[j] == 3 || cl[j] == 1) && cm[j] == 0 )
                continue;

            long xj = circles->at(j)[0];
            long yj = circles->at(j)[1];
            long rj = circles->at(j)[2];

            // are circle i and circle j connected ?
            long d2 = dist2(xi,yi,xj,yj);
            if( d2 <= ((ri+rj) * (ri+rj)) ) {

                // early exit
                if( (cli == 1 && clj == 3 && block(xi,yi,xj,yj)) ||
                    (cli == 3 && clj == 1 && block(xj,yj,xi,yi)) ) {
                    is_blocked = true;
                    return -1;
                }

                // if( seen[j] != -1 )
                //     continue;

                ret += dfs(j,comp,crosses_bottom_edge,crosses_left_edge,crosses_top_edge,crosses_right_edge);
            }
        }
        return ret;
    }

public:
    bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {
        this->xCorner = xCorner;
        this->yCorner = yCorner;
        this->circles = &circles;
        c_sz = circles.size();
        memset(seen,-1,sizeof seen);
        is_blocked = false;

        // circles[i] = [xi, yi, ri]

        // consider moving everything (increasing x and y) to not have to deal with negative coordinates

        // quick check
        // if bottom left or top right corner corner are inside a circle, then there is no solution
        // note that inside here also means touched

        // idea
        // there is no solution if there is a 'path'
        // (perimeter of a circle -> center of that circle -> ... center of a circle -> perimeter of circle)
        // the crosses (including starts) - bottom edge -> left edge
        //                                - bottom edge -> top edge
        //                                - right edge -> left edge
        //                                - right edge -> top edge
        // but only if those go from the inside out !
        // like a path 0 -> 1 -> 2 -> 3 -> 0 that does not connect the begin with the end also is not blocking


        // is bottom left inside a circle? is top right inside a circle?
        for(int i = 0; i < c_sz; ++i) {
            long x = circles[i][0];
            long y = circles[i][1];
            long r = circles[i][2];

            long r2 = r * r;

            long dist_bl_cc2 = dist2(0,0,x,y);
            if( r2 >= dist_bl_cc2 )
                return false;

            long dist_tr_cc2 = dist2(xCorner,yCorner,x,y);
            if( r2 >= dist_tr_cc2 )
                return false;

            if( x <= xCorner && y <= yCorner)
                cl[i] = 0;
            else if( x > xCorner && y <= yCorner )
                cl[i] = 1;
            else if( x <= xCorner && y > yCorner )
                cl[i] = 3;
            else // x > xCorner && y > yCorner
                cl[i] = 2;

            // if our circle center is inside and touches/crosses as outlined above
            cm[i] = get_mask(x,y,r);
            bool crosses_bottom_edge = cm[i] & 1;
            bool crosses_left_edge   = cm[i] & (1<<1);
            bool crosses_top_edge    = cm[i] & (1<<2);
            bool crosses_right_edge  = cm[i] & (1<<3);

            /*
            cout << "cirle i " << i << " x " << x << " y " << y << " r " << r << " cl " << cl[i] << endl;
            if( cl[i] == 3 ) {
                cout << " y - yCorner " << y - yCorner << " xCorner - x " << xCorner - x << endl;
            }
            cout << " crosses_bottom_edge " << crosses_bottom_edge << endl;
            cout << " crosses_left_edge   " << crosses_left_edge << endl;
            cout << " crosses_top_edge    " << crosses_top_edge << endl;
            cout << " crosses_right_edge  " << crosses_right_edge << endl;
            */

            if( crosses_bottom_edge && crosses_left_edge )
                return false;
            if( crosses_bottom_edge && crosses_top_edge )
                return false;
            if( crosses_right_edge && crosses_left_edge )
                return false;
            if( crosses_right_edge && crosses_top_edge )
                return false;
        }

        // at this point we can ignore circles in quadrant 2. period.

        int comp = 0;
        for(int i = 0; i < c_sz; ++i) {
            if( (cl[i] == 3 || cl[i] == 1) && cm[i] == 0 )
                continue;

            if( cl[i] != 2 && seen[i] == -1 ) {
                bool crosses_bottom_edge = false;
                bool crosses_left_edge   = false;
                bool crosses_top_edge    = false;
                bool crosses_right_edge  = false;

                int comp_sz = dfs(i,comp,crosses_bottom_edge,crosses_left_edge,crosses_top_edge,crosses_right_edge);
                if( is_blocked ) {
                    // cout << "here" << endl;
                    return false;
                }
                ++comp;

                if( crosses_bottom_edge && crosses_left_edge )
                    return false;
                if( crosses_bottom_edge && crosses_top_edge )
                    return false;
                if( crosses_right_edge && crosses_left_edge )
                    return false;

                // edge case
                if( comp_sz == 2 && crosses_right_edge && crosses_top_edge) {
                    // if point in quadrant 3 and another in quadrant 1
                    // and they don't block (they don't, otherwise we would not be here)
                    // we have a false positive if crosses_right_edge && crosses_top_edge

                    int p1 = -1;
                    int p2;
                    for(int j = 0; j < c_sz; ++j) {
                        if( seen[j] == comp-1 ) {
                            if( p1 == -1 ) {
                                p1 = j;
                            } else {
                                p2 = j;
                                break;
                            }
                        }
                    }
                    if( (cl[p1] == 1 && cl[p2] == 3) || (cl[p1] == 3 && cl[p2] == 1) )
                        continue;
                }

                if( crosses_right_edge && crosses_top_edge )
                    return false;
            }
        }

        return true;
    }
};



/*

3
4
[[2,1,1]]
3
3
[[1,1,2]]
3
3
[[2,1,1],[1,2,1]]
4
4
[[5,5,1]]
8
5
[[2,3,1],[5,4,1],[2,1,1],[5,4,1],[3,2,1],[5,2,2],[7,1,1]]
3
3
[[2,1000,997],[1000,2,997]]
22742157
210809967
[[22741186,210810964,200],[22741869,210809432,165],[22742256,210810275,182],[22742089,210809693,129],[22741912,210810128,196],[22741658,210809205,144],[22741648,210809094,118],[22741920,210809808,128]]
15
15
[[1,99,85],[99,1,85]]

*/


