


// 759. Employee Free Time
// https://leetcode.com/problems/employee-free-time/


/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {

        auto cmp = [](const Interval& a, const Interval& b) {
            if( a.start > b.start ) {
                return true;
            } else if( a.start == b.start ) {
                if( a.end > b.end)
                    return true;
            }
            return false;
        };
        priority_queue<Interval,vector<Interval>,decltype(cmp)> pq(cmp);
        for(int i = 0; i < schedule.size(); ++i)
            for(int j = 0; j < schedule[i].size(); ++j)
                pq.push(schedule[i][j]);


        vector<Interval> ans;
        ans.push_back(Interval(INT_MIN,INT_MAX));

        int start,end;
        while( !pq.empty() ) {
            start = pq.top().start;
            end   = pq.top().end;
            pq.pop();

            // cout << start << " " << end << endl;

            // process start of current interval
            if( start > ans.back().start ) {
                Interval a = Interval(ans.back().start,start);
                Interval b = Interval(end,INT_MAX);
                ans.pop_back();
                ans.push_back(a);
                ans.push_back(b);
            }
            // process end of current interval
            if( end > ans.back().start ) {
                ans.back().start = end;
            }
        }

        ans.erase(ans.begin());
        ans.pop_back();

        return ans;
    }
};
