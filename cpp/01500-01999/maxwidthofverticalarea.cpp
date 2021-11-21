
// 1637. Widest Vertical Area Between Two Points Containing No Points
// https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/


class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        sort(begin(points),end(points));
        int r = 0;
        for(auto it = next(begin(points)); it != end(points); ++it) {
            r = max(r, (*it)[0] - (*(prev(it)))[0]);
        }
        return r;
    }
};
