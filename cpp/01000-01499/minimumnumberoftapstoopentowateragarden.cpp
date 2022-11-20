
// 1326. Minimum Number of Taps to Open to Water a Garden
// https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/




class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        // transform ranges into intervals
        vector<array<int,2>> intervals;
        for(int i = 0; i <= n; ++i)
            if( ranges[i] > 0 )
                intervals.push_back({max(0,i-ranges[i]),min(n,i+ranges[i])});
        sort(intervals.begin(),intervals.end(),[](const array<int,2>& a, const array<int,2>& b){
           if( a[0] < b[0] ) {
               return true;
           } else if( a[0] == b[0] ) {
               if( a[1] < b[1] ) {
                   return true;
               }
            }
            return false;
        });

        /*
        for(auto& a: intervals)
            cout << a[0] << "," << a[1] << " ";
        cout << endl;
        */

        // quick test
        if( intervals.empty() || intervals.front()[0] > 0 )
            return -1;

        int ans = 0;

        // go left to right
        vector<array<int,2>> stck; // endpoint of intervals used so far
                                   // top will be the furthest endpoint
        stck.push_back({intervals[0][0],intervals[0][1]});

        for(int i = 1; i < intervals.size(); ++i) {
            // do we overlap or at least 'touch'?
            // if not -> end
            if( intervals[i][0] > stck.back()[1] )
                return -1;

            // are we gaining anything? greedy
            // if not -> skip
            if( intervals[i][1] < stck.back()[1] )
                continue;

            // can we eliminate previously used intervals?
            //     the starting point of the current interval
            //        will never be less than any interval used so far
            //     then endpoint of the current interval
            //        will never be less than any interval used so far
            while( !stck.empty() && stck.back()[0] == intervals[i][0] )
                stck.pop_back();

            if( !stck.empty() && intervals[i][0] < stck.back()[1] ) {

                while( stck.size() >= 2 && intervals[i][0] <= stck[stck.size()-2][1] )
                    stck.pop_back();

            }
            if( stck.empty() || intervals[i][1] > stck.back()[1] )
                stck.push_back({intervals[i][0],intervals[i][1]});
            if( stck.back()[1] == n )
                break;
        }

        /*
        for(auto& a: stck)
            cout << a[0] << "," << a[1] << " ";
        cout << endl;
        */

        return stck.back()[1] < n ? -1 : stck.size();
    }
};
