
// 2402. Meeting Rooms III
// https://leetcode.com/problems/meeting-rooms-iii/


class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // constraints
        //    1 <= n <= 100
        //    1 <= meetings.length <= 100000
        //    0 <= starti < endi <= 500000
        // so worst case if also all end times are unique, we would have 200000 unique times
        
        sort(meetings.begin(),meetings.end(),[](const vector<int>& a, const vector<int>& b){
            // start times are unique
            return a[0] < b[0];
        });      
                
        // free rooms by room idx
        priority_queue<int,vector<int>,greater<int>> free_rooms; 
        for(int i = 0; i < n; ++i)
            free_rooms.push(i);
        
        // busy rooms by meeting end time
        // pair<long,int> meeting end time, room idx
        auto cmp = [](const pair<long,int>& a, const pair<long,int>& b){
            return a.first > b.first;    
        };
        priority_queue<pair<long,int>,vector<pair<long,int>>,decltype(cmp)> busy_rooms(cmp);
        
        int cnt[n];memset(cnt,0,sizeof cnt); // count of meetings held in a given room
        long t = meetings[0][0]; // current time
        const int mtg_sz = meetings.size();
        for(int i = 0; i < mtg_sz; ) {
            // cout << "mtg " << i << " t " << t << endl;
            
            // free up any rooms based on the current time
            while( !busy_rooms.empty() && busy_rooms.top().first == t ) {
                free_rooms.push(busy_rooms.top().second);
                busy_rooms.pop();
            }
            // if we still don't have any free rooms, we need to advance the time
            // to when at least one room frees up
            if( free_rooms.empty() ) {
                t = busy_rooms.top().first;
                continue;
            }
            
            // we have at least one free room, but ...
            // if there are meetings that end before the current meeting starts, 
            // then we need to let those end first
            long curr_meeting_original_start_time = meetings[i][0];
            if( t >= curr_meeting_original_start_time ) {
                // we are already behind, so lets hold this meeting
                int room_idx = free_rooms.top();
                free_rooms.pop();
                ++cnt[room_idx];
                
                long curr_meeting_original_end_time = meetings[i][1];
                long curr_meeting_duration = curr_meeting_original_end_time - curr_meeting_original_start_time;
                
                long actual_end_time = t + curr_meeting_duration;
                busy_rooms.push({actual_end_time,room_idx});
                
                // advance the meeting;
                ++i;
                // advance the time
                long next_meeting_start = LONG_MAX;
                if( i < mtg_sz ) {
                    if( meetings[i][0] <= t )
                        next_meeting_start = t;
                    else
                        next_meeting_start = meetings[i][0];
                }
                long next_time_meetings_end = busy_rooms.top().first;
                t = min(next_meeting_start,next_time_meetings_end);
                

            } else {
                long next_time_meetings_end = !busy_rooms.empty() ? busy_rooms.top().first : LONG_MAX;
                t = min(curr_meeting_original_start_time,next_time_meetings_end);                  
            }
        }
        
        int mx_nbr_meetings = 0;
        int ans; // idx of room in which the most number of meetings where held
        for(int i = 0; i < n; ++i) {
            if( cnt[i] > mx_nbr_meetings ) {
                mx_nbr_meetings = cnt[i];
                ans = i;
            }
        }
        
        return ans;
    }
};
