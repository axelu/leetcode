
// 3454. Separate Squares II
// https://leetcode.com/problems/separate-squares-ii/


class Solution {
private:
    struct T {
        int covered;
        int l;
        int nominal_l;
        T() : covered(0), l(0), nominal_l(0) {}
        T(int covered, int nominal_l) : covered(covered), l(0), nominal_l(nominal_l) {}
    };

    vector<T> t; // segment tree; range sum, range addition (non-lazy)

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            // t[v] = T(0, 0, true, a[tl]);
            t[v].covered = 0;
            t[v].l = 0;
            t[v].nominal_l = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            // t[v] = T(0, 0, false, t[v*2] + t[v*2+1]);
            t[v].covered = 0;
            t[v].l = 0;
            t[v].nominal_l = t[v*2].nominal_l + t[v*2+1].nominal_l;
        }
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;

        if (l == tl && r == tr) {
            t[v].covered += addend;
        } else {
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        }

        // children are update at this point, which we need if not at leaf
        // if tl == tr we are at a leaf
        // is the segment this node represents completely covered?
        if( t[v].covered > 0 )
            t[v].l = t[v].nominal_l;
        else 
            t[v].l = tl == tr ? 0 : t[v*2].l + t[v*2+1].l;

        return;
    }    

    // binary search floating point
    double search(double s, double e, double len, double target) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e + 1e-6 )
            return -1.0;

        double mid = s + ((e-s)/2.0);
        double area = mid * len;

        if( area >= target + 1e-5) { // floating point compare
            double t = search(s, mid - 1e-6, len, target);
            return t != -1.0 ? t : mid;
        }

        return search(mid + 1e-6, e, len, target);
    }

public:
    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();

        // we will look at the squares along horizontal 'slivers'
        // building them bottom up aka we process them by increasing y
        // each square has two y coordinates, one representing the 
        // lower edge and the other the upper edge
        // while processing, we maintain a segment tree that sums
        // the current total covered length
        // then y - pre_y is height * current total covered length = area
        // we do this to calculate the total covererd area w/o double counting
        // of all sqares
        // we will keep track of the covered area in each slivers
        // and its running sum (like a prefixSum)
        // we can then run through this and determine in which sliver
        // we cross total_area/2 and can inch down to find the point
        // aka find the y where bottom and top area are total_area/2

        // intervals along the x-axis
        // interval    0       1       2
        //          ------- ------- -------
        // x        x0   x1 x1   x2 x2   x3
        // x0, x1, x2, ... are unique values along the x-axis
        // let l be the length of an interval l = x2 - x1

        // get unique x
        set<int> unique_x;
        for(auto& v: squares) {
            unique_x.insert(v[0]);
            unique_x.insert(v[0] + v[2]);
        }
        // cout << "unique_x.size() " << unique_x.size() << endl;
        // we have unique_x.size()-1 intervals along the x-axis
        // those intervals are the leaves in our segment tree
        unordered_map<int,int> begin_x_interval;
        unordered_map<int,int> end_x_interval;
        vector<int> intervals(unique_x.size()-1); // intervals along x-axis
        int interval_idx = 0;
        int x1 = *unique_x.begin();
        int x2;
        for(auto it = next(unique_x.begin()); it != unique_x.end(); ++it) {
            x2 = *it;
            begin_x_interval.insert({x1, interval_idx});
            end_x_interval.insert({x2, interval_idx});
            intervals[interval_idx] = x2 - x1;
            ++interval_idx;
            x1 = x2;
        }

        // get all horizontal dividers
        vector<vector<int>> horizontals;
        for(auto& v: squares) {
            int x = v[0];
            int y = v[1];
            int l = v[2];
            // lower edge our square begins
            horizontals.push_back({y, x, x+l, 1});
            // upper edge square ends, aka the coverage of x-axis segment ends
            horizontals.push_back({y+l, x, x+l, -1});
        }
        // cout << "horizontals.size() " << horizontals.size() << endl;

        sort(horizontals.begin(), horizontals.end(), [](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                //if( a[3] == -1 ) { // ends before begins
                //    return true;
                //}
                if( a[3] < b[3] ) { // ends before begins
                    return true;
                }
            }
            return false;
        });

        t.resize(4 * intervals.size());
        build(intervals, 1, 0, intervals.size()-1);

        double total_area = 0.0;

        // intervals along the y-axis: { y1, y2, l} where y1 < y2
        vector<vector<int>> slivers; 
        vector<double> prefixSum; // 0-indexed

        // the first horizontal in horizontals will be a start
        x1 = horizontals[0][1];
        int i1 = begin_x_interval[x1];
        x2 = horizontals[0][2];
        int i2 = end_x_interval[x2];
        update(1, 0, intervals.size()-1, i1, i2, 1);
        int pre_y = horizontals[0][0];

        for(int i = 1; i < horizontals.size(); ++i) {
            int y = horizontals[i][0];
            x1 = horizontals[i][1];
            i1 = begin_x_interval[x1];
            x2 = horizontals[i][2];
            i2 = end_x_interval[x2];
            int addend = horizontals[i][3];

            double height = y - pre_y;
            double len = t[1].l; // root node has the current covered length
            double area = height * len;
            total_area += area;

            if( y != pre_y ) {
                slivers.push_back({pre_y, y, (int)len});
                prefixSum.push_back(total_area);
            }

            update(1, 0, intervals.size()-1, i1, i2, addend);
            pre_y = y;
        }
        /*
        cout << "total_area " << total_area << endl;
        for(int i = 0; i < slivers.size(); ++i) { // slivers.size() == prefixSum.size()
            cout << "sliver " << i << " y1 " << slivers[i][0] << " y2 " << slivers[i][1] << " len " << slivers[i][2] << " prefixSum " << prefixSum[i] << endl;
        }
        */
       
        double total_area2 = total_area / 2.0;

        // TODO we could to a binary search, but would need to watch out
        // for the following: interval we get, answer maybe the lower edge,
        // but if the sliver below is empty, the answer is the top edge
        // of two intervals down
        // lets simplify and just walk up
        int i = 0;
        for(; i < prefixSum.size(); ++i) {
            if( prefixSum[i] >= total_area2 )
                break;
        }
        // we should never be at i == prefixSum.size()

        if( prefixSum[i] == total_area2 )
            return (double)slivers[i][1];

        // our answer is somewhere between slivers[i][0] and slivers[i][1]
        double area_below = 0.0;
        if( i > 0 )
            area_below = prefixSum[i-1];
        
        // cout << "answer between " << slivers[i][0] << " and " << slivers[i][1] << endl;
        double target = total_area2 - area_below;

        double y = search(0, slivers[i][1] - slivers[i][0], slivers[i][2], target);
        return (double)slivers[i][0] + y;
    }
};

/*

[[0,0,1],[2,2,1]]
[[0,0,2],[1,1,1]]
[[0,0,1]]
[[15,21,2],[19,21,3]]
[[0,0,9999999],[1000000000,0,9999999],[0,999999999,10000000],[0,1000000000,9999999],[1000000000,1000000000,9999999]]

*/
