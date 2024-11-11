
// 3288. Length of the Longest Increasing Path
// https://leetcode.com/problems/length-of-the-longest-increasing-path/





class Solution {
private:
    int t[200002]; // segment tree memory efficient indexing

    int get_max(int v, int tl, int tr, int l, int r) {
        // cout << "get_max v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    // binary search
    int search(vector<vector<int>>&coordinates, int s, int e, int kx, int ky) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( coordinates[mid][0] > kx && coordinates[mid][1] > ky ) {
            // can we do better?
            int t = search(coordinates, s, mid-1, kx, ky);
            return t != -1 ? t : mid;
        }

        return search(coordinates, mid+1, e, kx, ky);
    }

public:
    int maxPathLength(vector<vector<int>>& coordinates, int k) {
        // it is guaranteed that all elements in coordinates are distinct.
        int kx = coordinates[k][0];
        int ky = coordinates[k][1];

        // we will strip all points that are not the point at k
        // that are not to the upper right of the point at k or
        // that are not to the lower left of k

        // also: collect unique y coordinates
        set<int> unique_y_st;

        vector<vector<int>> points;
        for(auto& v: coordinates) {
            int x = v[0];
            int y = v[1];
            if( (kx < x && ky < y)   ||
                (kx == x && ky == y) ||
                (x < kx && y < ky) ) {

                points.push_back({x,y});
                unique_y_st.insert(y);
            }
        }

        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            // if we assume we are at point 4, then this is order
            // given all possible locations of the point to compare with
            // 2 5 8
            // 1 4 7
            // 0 3 6
           // test with [[2,1],[1,1],[0,1],[0,0],[0,2],[1,0],[2,2],[1,2],[2,0]]

            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        // debug
        /*
        for(int i = 0; i < points.size(); ++i)
            cout << points[i][0] << "," << points[i][1] << " ";
        cout << endl;
        */

        int yidx = 0;
        unordered_map<int,int> yidx_mp;
        for(auto it = unique_y_st.begin(); it != unique_y_st.end(); ++it)
            yidx_mp[*it] = yidx++;
        int m = yidx; // number of distinct y coordinates

        // at most we have 100,000 coordinates
        // memory efficient segment tree for max of size 200,002
        memset(t,0,sizeof t);

        int n = points.size();

        queue<pair<int,int>> q; // yidx, mx
        int cur_x = -1;

        int mx;
        for(int i = n-1; i >= 0; --i) {
            int x = points[i][0];
            int y = points[i][1];
            // cout << "i " << i << " x " << x << " y " << y << endl;

            if( x != cur_x ) {
                while( !q.empty() ) {
                    update(1, 0, m, q.front().first, q.front().second); // m, not m-1 !!!
                    q.pop();
                }
                cur_x = x;
            }

            mx = get_max(1, 0, m, yidx_mp[y]+1, m); // m not m-1; yidx_mp[y]+1 not yidx_mp[y], because we need to look for greater
            // cout << "mx so far " << mx << endl;
            q.push({yidx_mp[y], mx+1});
        }
        // finish up
        while( !q.empty() ) {
            update(1, 0, m, q.front().first, q.front().second); // m, not m-1 !!!
            q.pop();
        }


        return get_max(1, 0, m, 0, m);
    }
};
