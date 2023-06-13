
// 2345. Finding the Number of Visible Mountains
// https://leetcode.com/problems/finding-the-number-of-visible-mountains/



class Solution {
public:
    int visibleMountains(vector<vector<int>>& peaks) {
        int n = peaks.size();
        if( n == 1 )
            return 1;

        // turn peaks into intervals s,e
        vector<array<int,2>> intervals(n);
        for(int i = 0; i < n; ++i) {
            int s = peaks[i][0] - peaks[i][1];
            int e = peaks[i][0] + peaks[i][1];
            intervals[i] = {s,e};
        }

        sort(intervals.begin(),intervals.end(),[](const array<int,2>& a, const array<int,2>& b){
            if( a[0] < b[0] ) {
               return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        });

        int ans = 0;

        // deal with the visibility of the 1st peak,
        // we have at last two if we are here
        if( intervals[0][0] < intervals[1][0] ) {
            ans = 1;
        } else { // intervals[0][0] < intervals[1][0]
            if( intervals[0][1] > intervals[1][1] ) {
                ans = 1;
            }
        }

        // keep track of largest endpoint seen so far
        int mx_e = intervals[0][1];
        for(int i = 1; i < n; ++i)
            if( intervals[i][1] > mx_e ) {
                mx_e = intervals[i][1];
                // we cannot count this mountain
                // if same mountains exist
                bool f = false;
                while( i+1 < n && intervals[i+1][0] == intervals[i][0] &&  intervals[i+1][1] == intervals[i][1] ) {
                    f = true;
                    ++i;
                }
                if( !f )
                    ++ans;
            }

        return ans;
    }
};
