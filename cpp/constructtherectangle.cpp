
// 492. Construct the Rectangle
// https://leetcode.com/problems/construct-the-rectangle/




class Solution {
public:
    vector<int> constructRectangle(int area) {
        if( area == 1 ) return {1,1};

        // area = L * W; // Length * Width -> 1 <= area <= 10^7
        // L >= W
        // difference between length L and width W should be as small as possible
        // extreme: L = area and W = 1

        int W = sqrt(area);
        int L;
        for(; W >= 1; --W) {
            if( area % W == 0 ) {
                L = area/W;
                break;
            }
        }
        return {L,W};
    }
};
