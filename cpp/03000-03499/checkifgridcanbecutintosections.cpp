
// 3394. Check if Grid can be Cut into Sections
// https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/


class Solution {
private:

    bool can_divide(vector<vector<int>>& intervals) {

        // interval merge, merge intervals
        sort(begin(intervals),end(intervals));

        int n = intervals.size();
        vector<vector<int>> r;
        r.push_back(intervals[0]);
        int i = 0;
        for(int j = 1; j < n; ++j) {
            if( intervals[j].front() >= r[i].back() ) { // if end and start the same, they do not overlap, hence >=
                r.push_back(intervals[j]);
                ++i;
            } else if( intervals[j].back() > r[i].back() ) {
                r[i].back() = intervals[j].back();
            }
        }

        return r.size() >= 3;
    }

public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {


        vector<vector<int>> h; // horizontal
        vector<vector<int>> v; // vertical
        for(auto& rectangle: rectangles) {
            int x1 = rectangle[0];
            int x2 = rectangle[2];
            h.push_back({x1,x2});

            int y1 = rectangle[1];
            int y2 = rectangle[3];
            v.push_back({y1,y2});
        }

        return can_divide(h) || can_divide(v);
    }
};
