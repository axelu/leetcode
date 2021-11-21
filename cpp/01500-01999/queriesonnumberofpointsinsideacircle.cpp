
// 1828. Queries on Number of Points Inside a Circle
// https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/






class Solution {
private:
    // binary search lower bound
    // first element greater or equal than target
    int lowerBound(vector<vector<int>>& v, int s, int e, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( v[mid][0] >= target ) {
            // can we do better?
            int ans = lowerBound(v,s,mid-1,target);
            return ans != -1 ? ans : mid;
        } else {
            return lowerBound(v,mid+1,e,target);
        }
    }

public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        int m = points.size();
        int n = queries.size();
        vector<int> ans(n);

        sort(points.begin(),points.end());

        int r2,xmin,xmax,ymin,ymax,i,cnt,ed2;
        for(int j = 0; j < n; ++j) {
            xmin = queries[j][0] - queries[j][2];
            i = lowerBound(points,0,m-1,xmin);
            if( i == -1 ) {
                ans[j] = 0;
                continue;
            }

            xmax = queries[j][0] + queries[j][2];
            ymin = queries[j][1] - queries[j][2];
            ymax = queries[j][1] + queries[j][2];
            r2 = queries[j][2]*queries[j][2];

            cnt = 0;
            for(; i < m; ++i) {
                if( points[i][0] > xmax ) break;
                if( points[i][1] < ymin || points[i][1] > ymax ) continue;
                ed2 = (queries[j][0]-points[i][0])*(queries[j][0]-points[i][0])+(queries[j][1]-points[i][1])*(queries[j][1]-points[i][1]);
                if( ed2 <= r2 ) ++cnt;
            }
            ans[j] = cnt;
        }
        return ans;
    }
};
