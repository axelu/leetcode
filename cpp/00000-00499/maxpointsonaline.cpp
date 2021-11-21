
// 149. Max Points on a Line
// https://leetcode.com/problems/max-points-on-a-line/




// see also
// 1232. Check If It Is a Straight Line
// https://leetcode.com/problems/check-if-it-is-a-straight-line/



class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if( n == 1 )
            return 1;
        if( n == 2 )
            return 2;
        
        int ans = 2;
        
        int seen[n][n];memset(seen,0,sizeof seen);
        
        int xi,yi,xj,yj,xk,yk,t;
        for(int i = 0; i < n; ++i) {
            xi = points[i][0];
            yi = points[i][1];
            for(int j = 0; j < n; ++j) {
                if( j == i )
                    continue;
                
                if( seen[i][j] )
                    continue;
                
                seen[j][i] = 1;
                
                xj = points[j][0] - xi;
                yj = points[j][1] - yi;

                t = 2;
                for(int k = 0; k < n; ++k) {
                    if( k == i || k == j )
                        continue;

                    xk = points[k][0] - xi;
                    yk = points[k][1] - yi;
                    if( abs(xj * yk - xk * yj) == 0 )
                        ++t;
                }
                
                ans = max(ans,t);
            }
        }
        
        return ans;
    }
};
