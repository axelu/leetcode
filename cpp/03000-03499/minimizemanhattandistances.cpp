
// 3102. Minimize Manhattan Distances
// https://leetcode.com/problems/minimize-manhattan-distances/




/* Manhattan Distance between two points [x1,y1] and [x2, y2]:
 * abs(x1 - x2) + abs(y1 - y2)
 * lets expand that
 * max({ x1 - x2 + y1 - y2,
 *       --      ----
 *       x1 - x2 - y1 + y2,
 *.      --      ----
 *      -x1 + x2 + y1 - y2,
 *      -x1 + x2 - y1 + y2 })
 * based on hint
 * so if we look at a point in above expansion, we have either x1 + y1 OR x1 - y1
 * replace points as [xi - yi, xi + yi]
 * then max Manhattan Distance is
 * max(max(xi) - min(xi), max(yi) - min(yi)) over all i
 * example     Manhattan
 *    x  y      0  1  2  3
 * 0  3 10   0  0  8 15  7
 * 1  5 15   1  8  0 18 12
 * 2 10  2   2 15 18  0  8
 * 3  4  4   3  7 12  8  0
 * we can see max Manhatten is 18, if we remove point 2 our max becomes 12
 * now lets replace points with [xi - yi, xi + yi]
 *    x  y   xi - yi   xi + yi
 * 0  3 10     -7        13
 * 1  5 15    -10        20
 * 2 10  2      8        12
 * 3  4  4      0         8
 * max(max(xi) - min(xi), max(yi) - min(yi)) over all i is max(8 - (-10), 20 - 8) is 18
 * if we remove point 2, then we get
 * max(max(xi) - min(xi), max(yi) - min(yi)) over all i but 2 is max(0 - (-10), 20 - 8) is 12
 *
 */
class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        int n = points.size();

        vector<vector<int>> alt(n); // xi - yi, xi + yi
        for(int i = 0; i < n; ++i) {
            int x = points[i][0];
            int y = points[i][1];
            alt[i] = {x - y, x + y};
        }

        map<int,int> ys;
        map<int,vector<map<int,int>::iterator>> xs;
        for(int i = 0; i < n; ++i) {
            int x = alt[i][0];
            int y = alt[i][1];
            auto p = ys.insert({y, 1});
            if( !p.second )
                ++p.first->second;
            xs[x].push_back(p.first);
        }

        int x_gmn = xs.begin()->first;
        int x_gmx = xs.rbegin()->first;
        int y_gmn = ys.begin()->first;
        int y_gmx = ys.rbegin()->first;
        // cout << "x_gmn " << x_gmn << " x_gmx " << x_gmx << " y_gmn " << y_gmn << " y_gmx " << y_gmx << endl;
        int ans = max(x_gmx - x_gmn, y_gmx - y_gmn);
        // cout << "overall max manhattan " << ans << endl;

        for(auto itx = xs.begin(); itx != xs.end(); ++itx) {
            int x = itx->first;
            int x_lmn = x_gmn;
            if( itx == xs.begin() && itx->second.size() == 1 )
                x_lmn = next(itx)->first;
            int x_lmx = x_gmx;
            if( next(itx) == xs.end() && itx->second.size() == 1 )
                x_lmx = prev(itx)->first;

            for(auto ity = itx->second.begin(); ity != itx->second.end(); ++ity) {
                int y = (*ity)->first;
                int y_lmn = y_gmn;
                if( y == y_gmn && (*ity)->second == 1 )
                    y_lmn = next((*ity))->first;
                int y_lmx = y_gmx;
                if( y == y_gmx && (*ity)->second == 1 )
                    y_lmx = prev((*ity))->first;

                ans = min(ans, max(x_lmx - x_lmn, y_lmx - y_lmn));
            }
        }

        return ans;
    }
};
