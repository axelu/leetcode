
// 3169. Count Days Without Meetings
// https://leetcode.com/problems/count-days-without-meetings/




class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        int n = meetings.size();
        if( n == 1 )
            return days - (meetings[0][1] - meetings[0][0] + 1);

        sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        int meeting_days = 0;
        int curr_meeting_days  = meetings[0][1] - meetings[0][0] + 1;
        int curr_meeting_start = meetings[0][0];
        int curr_meeting_end   = meetings[0][1];
        for(int i = 1; i < n; ++i) {

            if( meetings[i][0] > curr_meeting_end ) {
                // no overlap with with prior meeting respectively a new meeting starts
                meeting_days += curr_meeting_days;
                curr_meeting_days  = meetings[i][1] - meetings[i][0] + 1;
                curr_meeting_start = meetings[i][0];
                curr_meeting_end   = meetings[i][1];

            } else if( meetings[i][0] == curr_meeting_end ) {
                // extension of prior meeting
                curr_meeting_days += meetings[i][1] - curr_meeting_end;
                curr_meeting_end  = meetings[i][1];

            } else if( meetings[i][0] > curr_meeting_start && meetings[i][0] < curr_meeting_end ) {
                if( meetings[i][1] > curr_meeting_end ) {
                    curr_meeting_days += meetings[i][1] - curr_meeting_end;
                    curr_meeting_end = meetings[i][1];
                }

            } else if( meetings[i][0] == curr_meeting_start ) {
                if( meetings[i][1] > curr_meeting_end ) {
                    curr_meeting_days += meetings[i][1] - curr_meeting_end;
                    curr_meeting_end = meetings[i][1];
                }

            } else { // meetings[i][0] < meetings[i-1][0]
                // nothing to do as this should never happen due to our sorting

            }
        }
        // finish up
        meeting_days += curr_meeting_days;

        return days - meeting_days;
    }
};
