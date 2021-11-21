
// day 13 September 2020 challenge
// 57. Insert Interval
// https://leetcode.com/problems/insert-interval/



class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if( intervals.empty() ) return {newInterval};

        int n_min = newInterval.front();
        int n_max = newInterval.back();
        if( n_max < intervals.front().front() ) {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        } else if ( n_min > intervals.back().back() ) {
            intervals.push_back(newInterval);
            return intervals;
        } else if ( n_min <= intervals.front().front() && n_max >= intervals.back().back() ) {
            return {newInterval};
        }

        bool inserted = false;
        vector<vector<int>> r;
        for(auto it = intervals.begin(); it != intervals.end(); ++it) {

            if( it->back() < newInterval.front() ) {
                r.push_back(*it);
                continue;
            }

            if( newInterval.back() < it->front() ) {
                if ( !inserted ) {
                    r.push_back(newInterval);
                    inserted = true;
                }
                r.push_back(*it);
                continue;
            }

            newInterval.front() = min(it->front(), newInterval.front());
            newInterval.back() = max(it->back(), newInterval.back());
        }

        if ( !inserted )
            r.push_back(newInterval);

        return r;
    }
};
