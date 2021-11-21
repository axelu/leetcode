
// 435. Non-overlapping Intervals
// https://leetcode.com/problems/non-overlapping-intervals/




class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {

        if ( intervals.empty() ) return 0;
        if ( intervals.size() == 1 ) return 0;

        sort(intervals.begin(),intervals.end());

        stack<vector<int>> stck;
        stck.push(intervals[0]);
        for(auto it = intervals.begin() + 1; it != intervals.end(); ++it) {
            if ( it->front() < stck.top().back() ) {
                if ( it->back() < stck.top().back() ) stck.top().back() = it->back();
            } else {
                stck.push(*it);
            }
        }

        return intervals.size() - stck.size();
    }
};
