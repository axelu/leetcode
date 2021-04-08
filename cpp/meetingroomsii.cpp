
// 253. Meeting Rooms II
// https://leetcode.com/problems/meeting-rooms-ii/

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        size_t n = intervals.size();
        if( n == 1 ) return 1;

        int ans = 1;
        sort(begin(intervals),end(intervals));
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[1] > b[1];
        };
        priority_queue< vector<int>,vector<vector<int>>,decltype(cmp) > meetingsInProgress(cmp);
        meetingsInProgress.push(intervals[0]);
        vector<int> meeting; // interval
        for(int i = 1; i < n; ++i) {
            while( !meetingsInProgress.empty() ) {
                meeting = meetingsInProgress.top();
                if( meeting[1] <= intervals[i][0] ) {
                    meetingsInProgress.pop(); // release meeting room
                } else {
                    break;
                }
            }
            meetingsInProgress.push(intervals[i]);
            ans = max(ans,(int)meetingsInProgress.size());
        }

        return ans;
    }
};
