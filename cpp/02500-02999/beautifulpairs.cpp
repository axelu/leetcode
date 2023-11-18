
// 2613. Beautiful Pairs
// https://leetcode.com/problems/beautiful-pairs/





/* the BIG leap to make is to view nums1 and nums2 as coordinates x and y on a 2D grid
 * example 1
 *     index     0  1  2  3  4
 *     nums1 x   1  2  3  2  4
 *     nums2 y   2  3  1  2  3
 * then the problem statement becomes:
 * find the one pair of points Pi and Pj with the smallest Manhattan distance,
 * if multiple, then find the lexicographically smallest.
 * from the problem description:
 * A pair of indices (i1, j1) is lexicographically smaller than (i2, j2) if i1 < i2 or i1 == i2 and j1 < j2.
 */
class Solution {
private:
    struct Point {
        int x;
        int y;
        int idx;
        Point(int x, int y, int idx) : x(x), y(y), idx(idx) {};
    };

    int lower_bound(vector<Point*>& points, int s, int e, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        // int s = 0;
        // int e = n; // n = nums.size()
        int n = e;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= points[mid]->x )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && points[s]->x < target )
            ++s;

        return s;
    }

    int geltoret(vector<Point*>& points, int s, int e, int target) {
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        // int s = 0;
        // int e = n; // n = nums.size()
        int n = e;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( points[mid]->x > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && points[s]->x > target) || s == n )
            --s;

        return s;
    }

    int md(Point* p1, Point* p2) {
            // manhattan distance |xi - xj| + |yi - yj|
            return abs(p1->x - p2->x) + abs(p1->y - p2->y);
    }

    pair<Point*,Point*> make_point_pair(Point* p1, Point* p2) {
        return p1->idx < p2->idx ? make_pair(p1,p2) : make_pair(p2,p1);
    }

    pair<Point*,Point*> solve(vector<pair<Point*,Point*>>& v) {

        sort(v.begin(),v.end(),[](const pair<Point*,Point*>& a, const pair<Point*,Point*>& b){
            // cout << "pair a " << a.first->idx << " " << a.second->idx << endl;
            int mda = abs(a.first->x - a.second->x) + abs(a.first->y - a.second->y); // manhattan distance pair a
            // cout << "pair b " << b.first->idx << " " << b.second->idx << endl;
            int mdb = abs(b.first->x - b.second->x) + abs(b.first->y - b.second->y); // manhattan distance pair b
            if( mda < mdb ) {
                return true;
            } else if( mda == mdb ) {
                int ia = a.first->idx;
                int ja = a.second->idx;
                int ib = b.first->idx;
                int jb = b.second->idx;
                if( ia < ib ) {
                    return true;
                } else if( ia == ib ) {
                    if( ja < jb ) {
                        return true;
                    }
                }
            }
            return false;
        });

        return v[0];
    }

    pair<Point*,Point*> solve(vector<Point*>& points, int s, int e) {
        Point* p1 = points[s];
        Point* p2 = points[s+1];
        if( e - s + 1 == 2 )
            return make_point_pair(p1,p2);

        Point* p3 = points[e];

        //        p1 p2 p3
        // pair0  x  x
        // pair1     x  x
        // pair2  x     x

        vector<pair<Point*,Point*>> v(3);
        v[0] = make_point_pair(p1,p2);
        v[1] = make_point_pair(p2,p3);
        v[2] = make_point_pair(p1,p3);
        return solve(v);
    }

    pair<Point*,Point*> rec(vector<Point*>& points, int s, int e) {
        //cout << "rec s " << s << " e " << e << endl;
        // if we have only two points, we simply return the pair
        // if we have three points, we return the pair with smallest Manhattan distance (lexicographically smallest)
        if( e - s + 1 <= 3 )
            return solve(points,s,e);

        // divide
        int mid = s + ((e-s)/2);
        pair<Point*,Point*> lft = rec(points,s,mid);
        //cout << "rec s " << s << " e " << e << " win lft " << lft.first->idx << " " << lft.second->idx << " " << md(lft.first,lft.second) << endl;
        pair<Point*,Point*> rgt = rec(points,mid+1,e);
        //cout << "rec s " << s << " e " << e << " win rgt " << rgt.first->idx << " " << rgt.second->idx << " " << md(rgt.first,rgt.second) << endl;

        // merge
        vector<pair<Point*,Point*>> tmp{lft,rgt};
        pair<Point*,Point*> win = solve(tmp);
        //cout << "rec s " << s << " e " << e << " win tmp " << win.first->idx << " " << win.second->idx <<  " " << md(win.first,win.second) << endl;

        // merge including cross
        tmp = {win};
        // we basically divided our points by an x-coordinate mid so far,
        // so we still need to process all points [s,e]
        // where (mid - min_manhattan) <= points[i]->x <= (mid + min_manhattan)
        // int min_manhattan = min(lft_manhattan,rgt_manhattan);
        int min_manhattan = md(win.first,win.second);
        // cout << "rec s " << s << " e " << e << " min_mahattan " << min_manhattan << endl;

        if( min_manhattan > 0 ) {
        // points left of mid within manhattan distance from mid
        int slft = lower_bound(points,s,mid+1,points[mid]->x-min_manhattan);
        int elft = mid;

        // points right of mid within manhattan distance from mid
        int srgt = mid + 1;
        int ergt = geltoret(points,mid+1,e+1,points[mid]->x+min_manhattan);

        // create all pairs and solve including the above winner
        // if( slft <= mid && ergt >= mid + 1 ) {
            for(int i = slft; i <= mid; ++i)
                for(int j = srgt; j <= ergt; ++j)
                    tmp.push_back(make_point_pair(points[i],points[j]));
        // }
        }
        return solve(tmp);
    }

public:
    vector<int> beautifulPair(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // nums1.size() == nums2.size();

        vector<Point*> points(n);
        for(int i = 0; i < n; ++i)
            points[i] = new Point(nums1[i],nums2[i],i);

        // sort points by x, idx
        sort(points.begin(),points.end(),[](const Point* a, const Point* b) {
            if( a->x < b->x ) {
                return true;
            } else if( a->x == b->x ) {
                if( a->idx < b->idx ) {
                    return true;
                }
            }
            return false;
        });
        /*
        for(int i = 0; i < n; ++i) {
            cout << i << ": " << points[i]->x << " " << points[i]->y << " " << points[i]->idx << endl;
        }
        */

        auto p = rec(points,0,n-1);
        int i = p.first->idx;
        int j = p.second->idx;

        /*
        cout << md(p.first,p.second) << endl;
        int ansi = 2;
        int ansj = 50;
        Point* pansi = new Point(nums1[ansi],nums2[ansi],ansi);
        Point* pansj = new Point(nums1[ansj],nums2[ansj],ansj);
        cout << md(pansi,pansj) << endl;
        */

        return {i,j};
    }
};
