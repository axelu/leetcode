
// 757. Set Intersection Size At Least Two
// https://leetcode.com/problems/set-intersection-size-at-least-two/






class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // sort by endpoint
        sort(intervals.begin(),intervals.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[1] < b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] < b[0] ) {
                    return true;
                }
            }
            return false;
        });

        vector<int> v; // containing set
        // lets keep track of the last two positions and reuse those as long as possible (greedy)
        v.push_back(intervals[0][1]-1);
        v.push_back(intervals[0][1]);

        for(int i = 1; i < n; ++i) {
            int cur_s = intervals[i][0];
            int cur_e = intervals[i][1];

            if( cur_s > v.back() ) {
                // we cannot cover the current interval with our last two positions
                v.push_back(cur_e-1);
                v.push_back(cur_e);
            } else if( cur_s == v.back() || cur_s >  v[v.size()-2] ) {
                // we can cover the current interval with one position only
                v.push_back(cur_e);
            }
        }

        return v.size();
    }
};
