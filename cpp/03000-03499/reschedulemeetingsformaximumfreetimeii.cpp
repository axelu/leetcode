
// 3440. Reschedule Meetings for Maximum Free Time II
// https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/




class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        startTime.insert(startTime.begin(),0);
        endTime.insert(endTime.begin(),0);
        startTime.push_back(eventTime);
        endTime.push_back(eventTime);

        int n = startTime.size(); // startTime.size() == endTime.size()

        // pass1
        int first_gap = -1; // end point (could be 0) where next start > end point
        int last_gap = -1;  // start point (could be eventTime) where prev end < start
        int gap_count = 0;
        vector<int> maxgapleft(n+1,0); // largest gap up to i
        for(int i = 1; i < n; ++i) {
            if( endTime[i-1] < startTime[i]  ) {
                if( first_gap == -1 )
                    first_gap = endTime[i-1];
                last_gap = startTime[i];
                ++gap_count;
            }
            maxgapleft[i] = max(maxgapleft[i-1], startTime[i] - endTime[i-1]);
        }

        if( first_gap == -1 )
            return 0;
        if( gap_count == 1 )
            return last_gap - first_gap;

        int maxgap = 0;
        int maxgapright = 0;
        for(int i = n-2; i >= 1; --i) {
            // 4 cases
            // no gap left no gap right: -
            //    gap left no gap right: gap left OR gap left + us if we can unplug us
            // no gap left    gap right: gap right OR gap right + us if we can unplug us
            //    gap left    gap right: gap left + gap right OR gap left + gap right + us if we can unplug us
            //
            // unplug means there is a gap left or right we fit in

            int cur = endTime[i] - startTime[i];
            int gapleft = startTime[i] - endTime[i-1];
            int gapright = startTime[i+1] - endTime[i];

            if( gapleft == 0 && gapright == 0 ) {
                // do nothing

            } else if( gapright == 0 ) {
                if( maxgapleft[i-1] >= cur || maxgapright >= cur )
                    maxgap = max(maxgap, gapleft + cur);
                else
                    maxgap = max(maxgap, gapleft);

            } else if( gapleft == 0 ) {
                if( maxgapleft[i-1] >= cur || maxgapright >= cur )
                    maxgap = max(maxgap, cur + gapright);
                else
                    maxgap = max(maxgap, gapright);

            } else { // gapleft != 0 && gapright != 0
                if( maxgapleft[i-1] >= cur || maxgapright >= cur )
                    maxgap = max(maxgap, gapleft + cur + gapright);
                else
                    maxgap = max(maxgap, gapleft + gapright);

            }

            maxgapright = max(maxgapright, gapright);
        }

        return maxgap;
    }
};
