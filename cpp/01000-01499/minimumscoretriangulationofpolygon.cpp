
// 1039. Minimum Score Triangulation of Polygon
// https://leetcode.com/problems/minimum-score-triangulation-of-polygon/



/*
 *  what we are looking for is the min sum of the current trianlge plus
 *      the min of the adjacent areas
 *
 *                                   adjacent   adjacent
 *                trianlge i,j,k  +  area     + area
 *                                   i k        j k
 *  0 2:          triangle 1 2 3                         only one triangle
 *
 *  0 3:  min of  triangle 0 1 3   +            1 3 or
 *                triangle 0 2 3   + 0 2
 *
 *  0 4:  min of  triangle 0 1 4   +            1 4 or
 *                triangle 0 2 4   + 0 2      + 2 4 or
 *                triangle 0 3 4   + 0 3
 *
 *  0 5:  min of  triangle 0 1 5   +            1 5 or
 *                triangle 0 2 5   + 0 2      + 2 5 or
 *                triangle 0 3 5   + 0 3      + 3 5 or
 *                triangle 0 4 5   + 0 4
 *
 *  and so on
 */
class Solution {
private:
    int mem[50][50];

    int rec(vector<int>& values, int i, int k) {
        if( k - i == 1 ) // there is no adjacent area
            return 0;

        if( mem[i][k] != -1 )
            return mem[i][k];

        int ret = INT_MAX;

        int t,l,r;
        for(int j = i + 1; j < k; ++j) {
            // calculating triangle product
            t = values[i] * values[j] * values[k];

            // calculating adjacent areas
            int l = rec(values,i,j);
            int r = rec(values,j,k);

            ret = min(ret, t + l + r);
        }

        return mem[i][k] = ret;
    }
public:
    int minScoreTriangulation(vector<int>& values) {
        memset(mem,-1,sizeof mem);
        return rec(values,0,values.size()-1);
    }
};
