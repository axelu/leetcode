
// 223. Rectangle Area
// https://leetcode.com/problems/rectangle-area/


// inspired by
// https://www.geeksforgeeks.org/find-two-rectangles-overlap/
// https://www.geeksforgeeks.org/total-area-two-overlapping-rectangles/
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        // rectangle 1
        long a1 = (C-A) * (D-B);
        // rectangle 2
        long a2 = (G-E) * (H-F);
        // intersection
        // start from max(l1.x, l2.x) of x-coordinate and
        // end at min(r1.x,r2.x) x-coordinate by subtracting
        // start from end we get required lengths
        long x_dist = (long)min(C,G) - (long)max(A,E);
        long y_dist = (long)min(D,H) - (long)max(B,F);
        long ai = 0;
        if( x_dist > 0 && y_dist > 0 )
            ai = x_dist * y_dist;

        return (int)(a1 + a2 - ai);
    }
};
