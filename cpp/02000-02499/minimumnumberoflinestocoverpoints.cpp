
// 2152. Minimum Number of Lines to Cover Points
// https://leetcode.com/problems/minimum-number-of-lines-to-cover-points/



class Solution {
private:
    int mem[1024];

    int rec(vector<vector<int>>& points, int& n, int i, int& state) {
        if( i == n - 1 )
            return (state >> i) & 1 ? 0 : 1;

        if( mem[state] != -1 )
           return mem[state];

        int ret = 10;

        if( (state >> i) & 1 ) {
            // if the current point is already covered move on
            ret = rec(points,n,i+1,state);

        } else {
            // we have a choice
            // draw a line to any other point

            state |= 1 << i;                // mark Pi as covered
            int xi = points[i][0];
            int yi = points[i][1];
            int xj,yj,xk,yk;
            vector<int> v;
            int seen[n][n];memset(seen,0,sizeof seen);
            for(int j = 0; j < n; ++j) {
                v.clear();
                if( j == i )
                    continue;

                if( (state >> j) & 1 )
                    continue;

                if( seen[i][j] )
                   continue;

                seen[i][j] = 1;

                state |= 1 << j;            // mark Pj as covered
                xj = points[j][0] - xi;
                yj = points[j][1] - yi;

                // find all points that are
                // on the same line as Pi and Pj
                for(int k = 0; k < n; ++k) {
                    if( k == i || k == j )
                        continue;

                    xk = points[k][0] - xi;
                    yk = points[k][1] - yi;
                    if( abs(xj * yk - xk * yj) == 0 ) {
                        seen[i][k] = 1;
                        seen[j][k] = 1;
                        if(  !((state >> k) & 1) ) {
                            state |= 1 << k; // mark Pk as covered
                            v.push_back(k);
                        }
                    }
                }

                ret = min(ret,1 + rec(points,n,i+1,state));

                // backtrack
                state &= ~(1 << j);
                for(int k : v)
                    state &= ~(1 << k);
            }
            // backtrack
            state &= ~(1 << i);
        }

        return mem[state] = ret;
    }
public:
    int minimumLines(vector<vector<int>>& points) {
        int n = points.size();
        if( n < 3 )
            return 1;

        int state = 0;
        memset(mem,-1,sizeof mem);
        return rec(points,n,0,state);
    }
};
