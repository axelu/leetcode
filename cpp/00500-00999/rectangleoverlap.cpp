
// 830. Rectangle Overlap
// https://leetcode.com/problems/rectangle-overlap/



class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // rec1 [x1, y1, x2, y2] -> x1,y1 bottom-left; x2,y2 -> top-right
        // rec2 [x1, y1, x2, y2] -> x1,y1 bottom-left; x2,y2 -> top-right

        long x_dist = (long)min(rec1[2],rec2[2]) - (long)max(rec1[0],rec2[0]);
        long y_dist = (long)min(rec1[3],rec2[3]) - (long)max(rec1[1],rec2[1]);
        return x_dist > 0 && y_dist > 0;
    }
};
