
// 2280. Minimum Lines to Represent a Line Chart
// https://leetcode.com/problems/minimum-lines-to-represent-a-line-chart/





class Solution {
private:
    // convex polygon
    // Graham scan
    // for three points p(p0,p1), q(q0,q1) and r(r0,r1)
    // compute the z-coordinate of the cross product
    // of the two vectors p->q and p->r
    // if 0 the points are collinear
    int orientation(vector<vector<int>>& stockPrices, int p, int q, int r) {
        return (long)(stockPrices[q][1] - stockPrices[p][1]) * (long)(stockPrices[r][0] - stockPrices[q][0]) - (stockPrices[q][0] - stockPrices[p][0]) * (long)(stockPrices[r][1] - stockPrices[q][1]);
    }

public:
    int minimumLines(vector<vector<int>>& stockPrices) {
        int n = stockPrices.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return 1;

        sort(stockPrices.begin(),stockPrices.end());

        int ans = 1;
        for(int i = 0; i <= n-3; ++i) {
            if( orientation(stockPrices,i,i+1,i+2) != 0 )
                ++ans;
        }

        return ans;
    }
};
