
// 56. Merge Intervals
// https://leetcode.com/problems/merge-intervals/
// day 18 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/566/week-3-november-15th-november-21st/3535/





class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        size_t n = intervals.size();
        if( n == 1 ) return intervals;

        sort(begin(intervals),end(intervals));

        vector<vector<int>> r;
        r.push_back(intervals[0]);
        int i = 0;
        for(int j = 1; j < n; ++j) {
            if( intervals[j].front() > r[i].back() ) {
                r.push_back(intervals[j]);
                ++i;
            } else if( intervals[j].front() == r[i].back() ) {
                r[i].back() = intervals[j].back();
            } else if( intervals[j].back() > r[i].back() ) {
                // r[i].front() <= intervals[j].front() < r[i].back()
                r[i].back() = intervals[j].back();
            }
        }
        return r;
    }
};
