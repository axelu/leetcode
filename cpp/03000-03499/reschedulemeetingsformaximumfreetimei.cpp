
// 3439. Reschedule Meetings for Maximum Free Time I
// https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/




class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        // add sentinels
        startTime.insert(startTime.begin(),0);
        endTime.insert(endTime.begin(),0);
        startTime.push_back(eventTime);
        endTime.push_back(eventTime);

        int n = startTime.size(); // startTime.size() == endTime.size()

        // pass1
        int first_gap = -1; // end point (could be 0) where next start > end point
        int last_gap = -1;  // start point (could be eventTime) where prev end < start
        int gap_count = 0;
        for(int i = 1; i < n; ++i) {
            if( endTime[i-1] < startTime[i]  ) {
                if( first_gap == -1 )
                    first_gap = endTime[i-1];
                last_gap = startTime[i];
                ++gap_count;
            }
        }

        if( first_gap == -1 )
            return 0;
        if( gap_count == 1 )
            return last_gap - first_gap;

        // sliding window
        int maxgap = 0;
        int rungap = 0;
        int intervals = 0;
        int i = 0; // i left index
        for(; ; ++i)
            if( endTime[i] == first_gap)
                break;
        for(int j = i+1; j < n; ++j) {
            rungap += startTime[j] - endTime[j-1];
            maxgap = max(maxgap, rungap);

            if( intervals == k ) {
                rungap -= startTime[i+1] - endTime[i];
                ++i;
                --intervals;
            }
            ++intervals;
        }

        return maxgap;
    }
};
