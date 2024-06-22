
// 3111. Minimum Rectangles to Cover Points
// https://leetcode.com/problems/minimum-rectangles-to-cover-points/




class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        int n = points.size();

        sort(points.begin(),points.end(),[](const vector<int>& a, const vector<int>& b){
           return a[0] < b[0];
        });

        int ans = 0;
        int i = 0;
        int j = n-1;

        while( i <= j ) {
            ++ans;
            int si = points[i][0];
            while( i + 1 < n && points[i+1][0] - si <= w )
                ++i;

            if( i >= j )
                break;

            ++ans;
            int sj = points[j][0];
            while( j - 1 >= 0  && sj - points[j-1][0] <= w )
                --j;

            ++i;
            --j;
        }


        return ans;
    }
};
