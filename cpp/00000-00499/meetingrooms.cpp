
// 252. Meeting Rooms
// https://leetcode.com/problems/meeting-rooms/


class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        size_t n = intervals.size();
        sort(begin(intervals),end(intervals));
        for(int i = 1; i < n; ++i)
             if( intervals[i][0] < intervals[i-1][1] ) return false;            
        return true;
    }
};
