
// 3464. Maximize the Distance Between Points on a Square
// https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/

class Solution {
private:
    
    bool solve(vector<vector<int>>& points, int k, int d) {
        int n = points.size();

        for(int i = 0; i <= n-k; ++i) {
            int fstx = points[i][0];
            int fsty = points[i][1];

            int prex = points[i][0];
            int prey = points[i][1];
            int K = k-1;
            int manhattan;        
            for(int j = i+1; j < n && K > 0; ++j) {
                // returns 'n' if target greater than greatest element
                // returns  0  if target less or equal than smallest element
                // binary search lower bound while loop
                // lower bound -> equal or greater than target
                int s = j;
                int e = n; // n = nums.size()
                int mid;
                while(s < e) {
                    mid = s + ((e-s)/2);
                    manhattan = abs(prex - points[mid][0]) + abs(prey - points[mid][1]);
                    if( d <= manhattan )
                        e = mid;
                    else
                        s = mid+1;
                }
                if( s < n )
                    manhattan = abs(prex - points[s][0]) + abs(prey - points[s][1]);
                if( s < n && manhattan < d )
                    ++s;

                if( s == n )
                    break;

                prex = points[s][0];
                prey = points[s][1];
                --K;
                j = s;
            }
            if( K == 0 ) {
                manhattan = abs(prex - fstx) + abs(prey - fsty);
                if( manhattan >= d )
                    return true;
            }
        }
        return false;
    }

    // binary search
    int search_dist(vector<vector<int>>& points, int k, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(points, k, mid);
        if( f ) {
            // can we do better?
            int t = search_dist(points, k, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search_dist(points, k , s, mid-1);
    }

public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        // 1 <= side <= 1e9
        // 4 <= points.length <= min(4 * side, 15 * 1e3)
        // points.length worst case 15000
        // 15000 / 4 = 3750
        // 4 <= k <= min(25, points.length)
        // k worst case 25
        // all points are unique

        // edge case points.size() == k

        // max
        // the largest possible Manhattan distance is
        // between 2 diagonal corners of the sqaure
        // but because we have at least 4 points, the
        // possible max would be side, because best case
        // would be 4 points only, each optimally set
        // like on the respective corner of the square or
        // in the 'middle' of each side

        // min
        // as all points are unique, they are at least 1 apart

        // what if we pick some starting point and walk
        // around the perimiter of the square, only picking
        // points that are at least 'target' apart. If we can
        // pick k points, we have a solution, if not, we
        // need to try with a lower target => binary search
        // but we would need to try from each point

        // sort points counterclockwise
        // 0,0 would be point 0 if it exists
        sort(begin(points), end(points), [&side](const vector<int>& a, vector<int>& b){
            // point on lower edge 0 <= x <  side, y == 0           edge0
            // point on right edge x == side,      0 <= y <  side   edge1
            // point on top edge   0 < x <= side,  y == side        edge2
            // point on left edge  x == 0,         0 < y <= side    edge3

            int xa = a[0];
            int ya = a[1];
            int edgea;
            if( ya == 0 ) {
                edgea = xa < side ? 0 : 1;
            } else if( ya == side ) {
                edgea = xa > 0 ? 2 : 3;
            } else {
                edgea = xa == 0 ? 3 : 1;
            }

            int xb = b[0];
            int yb = b[1];
            int edgeb;
            if( yb == 0 ) {
                edgeb = xb < side ? 0 : 1;
            } else if( yb == side ) {
                edgeb = xb > 0 ? 2 : 3;
            } else {
                edgeb = xb == 0 ? 3 : 1;
            }

            if( edgea < edgeb ) {
                return true;
            } else if( edgea == edgeb ) {
                if( edgea == 0 )
                    return xa < xb;
                else if( edgea == 1 )
                    return ya < yb;
                else if( edgea == 2 )
                    return xa > xb;
                else
                    return ya > yb;
            }

            return false;
        });
        /*
        for(int i = 0; i < points.size(); ++i)
            cout << i << ":" << points[i][0] << "," << points[i][1] << " ";
        cout << endl;
        */
        // bool t = solve(points, k , 7);
        // return t;

        return search_dist(points, k, 1, side);
    }
};


// passes 610/619 test cases, than TLE as of 2/25/2025
// checked that it would however deliver correct result on that test
// but obviously to slow
// for this to pass, also had to do a binary search for next
// point to pick instead of just going point by point


class Solution {
private:

    // TODO improve this
    bool solve(vector<vector<int>>& points, int k, int d) {
        cout << "  solve d " << d << endl;
        int n = points.size();

        for(int i = 0; i <= n-k; ++i) {
            int fstx = points[i][0];
            int fsty = points[i][1];

            int prex = points[i][0];
            int prey = points[i][1];
            int K = k-1;
            int manhattan;
            for(int j = i+1; j < n && K > 0; ++j) {
                // find the next point to pick
                int x = points[j][0];
                int y = points[j][1];
                // Manhattan distance
                manhattan = abs(prex - x) + abs(prey - y);
                if( manhattan < d )
                    continue;

                prex = x;
                prey = y;
                --K;
            }
            if( K == 0 ) {
                manhattan = abs(prex - fstx) + abs(prey - fsty);
                if( manhattan >= d )
                    return true;
            }
        }
        return false;
    }

    // binary search
    int search(vector<vector<int>>& points, int k, int s, int e) {
        cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(points, k, mid);
        if( f ) {
            // can we do better?
            int t = search(points, k, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(points, k , s, mid-1);
    }

public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        // 1 <= side <= 1e9
        // 4 <= points.length <= min(4 * side, 15 * 1e3)
        // points.length worst case 15000
        // 15000 / 4 = 3750
        // 4 <= k <= min(25, points.length)
        // k worst case 25
        // all points are unique

        // edge case points.size() == k

        // max
        // the largest possible Manhattan distance is
        // between 2 diagonal corners of the sqaure
        // but because we have at least 4 points, the
        // possible max would be side, because best case
        // would be 4 points only, each optimally set
        // like on the respective corner of the square or
        // in the 'middle' of each side

        // min
        // as all points are unique, they are at least 1 apart

        // what if we pick some starting point and walk
        // around the perimiter of the square, only picking
        // points that are at least 'target' apart. If we can
        // pick k points, we have a solution, if not, we
        // need to try with a lower target => binary search
        // but we would need to try from each point

        // sort points counterclockwise
        // 0,0 would be point 0 if it exists
        sort(begin(points), end(points), [&side](const vector<int>& a, vector<int>& b){
            // point on lower edge 0 <= x <  side, y == 0           edge0
            // point on right edge x == side,      0 <= y <  side   edge1
            // point on top edge   0 < x <= side,  y == side        edge2
            // point on left edge  x == 0,         0 < y <= side    edge3

            int xa = a[0];
            int ya = a[1];
            int edgea;
            if( ya == 0 ) {
                edgea = xa < side ? 0 : 1;
            } else if( ya == side ) {
                edgea = xa > 0 ? 2 : 3;
            } else {
                edgea = xa == 0 ? 3 : 1;
            }

            int xb = b[0];
            int yb = b[1];
            int edgeb;
            if( yb == 0 ) {
                edgeb = xb < side ? 0 : 1;
            } else if( yb == side ) {
                edgeb = xb > 0 ? 2 : 3;
            } else {
                edgeb = xb == 0 ? 3 : 1;
            }

            if( edgea < edgeb ) {
                return true;
            } else if( edgea == edgeb ) {
                if( edgea == 0 )
                    return xa < xb;
                else if( edgea == 1 )
                    return ya < yb;
                else if( edgea == 2 )
                    return xa > xb;
                else
                    return ya > yb;
            }

            return false;
        });
        /*
        for(int i = 0; i < points.size(); ++i)
            cout << i << ":" << points[i][0] << "," << points[i][1] << " ";
        cout << endl;
        */
        bool t = solve(points, k ,4999);
        return t;

        return search(points, k, 1, side);
    }
};
