
// 1499. Max Value of Equation
// https://leetcode.com/problems/max-value-of-equation/




class Solution {
private:
    int t[400000]; // segment tree

    void build(vector<vector<int>>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl][0] + a[tl][1];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = max(t[v*2],t[v*2+1]);
        }
    }

    int get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INT_MIN;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v*2, tl, tm, l, min(r, tm)), get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        int n = points.size();

        // maximize equation: yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
        // it is guaranteed that xi < xj for all 1 <= i < j <= points.length (1-indexed) respectively
        // it is guaranteed that xi < xj for all 0 <= i < j < points.length (0-indexed) respectively
        // we can rewrite the equation:
        // yi + yj + (xj - xi) -> yi - xi + yj + xj
        // example
        // k = 1
        //             0     1     2     3
        // points      1,3   2,0   5,10  6,-10
        // pair 0 1    xj - xi = 2 - 1 <= k true, yi - xi + yj + xj = 3 - 1 + 0 + 2 = 4
        // pair 0 2    xj - xi = 5 - 1 <= k false
        // pair 0 3    xj - xi = 6 - 1 <= k false
        // pair 1 2    xj - xi = 5 - 2 <= k false
        // pair 1 3    xj - xi = 6 - 2 <= k false
        // pair 2 3    xj - xi = 6 - 5 <= k true, yi - xi + yj + xj = 10 - 5 + (-10) + 6 = 1
        // max(4,1) -> ans = 4

        build(points,1,0,n-1);

        int ans = INT_MIN;

        int j = 0;
        for(int i = 0; i < n-1; ++i) {
            j = max(j,i);
            // advance j as far as we can
            //                  xj               xi
            //             --------------   -------------
            while( j < n-1 && points[j+1][0] - points[i][0] <= k ) {
                ++j;
            }
            if( j > i )
                ans = max(ans, points[i][1] - points[i][0] + get_max(1,0,n-1,i+1,j));
        }

        return ans;
    }
};
