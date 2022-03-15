
// 1274. Number of Ships in a Rectangle
// https://leetcode.com/problems/number-of-ships-in-a-rectangle/



/**
 * // This is Sea's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Sea {
 *   public:
 *     bool hasShips(vector<int> topRight, vector<int> bottomLeft);
 * };
 */

class Solution {
private:
    int rec(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        if( topRight[0] < bottomLeft[0] || topRight[1] < bottomLeft[1] )
            return 0;

        if( !sea.hasShips(topRight,bottomLeft) )
            return 0;

        if( topRight[0] == bottomLeft[0] && topRight[1] == bottomLeft[1] )
            return 1;

        int mid_x = bottomLeft[0] + ((topRight[0]-bottomLeft[0])/2);
        int mid_y = bottomLeft[1] + ((topRight[1]-bottomLeft[1])/2);

        /*   b | c
         *   --+--
         *   a | d
         */

        int a = rec(sea,{mid_x,mid_y},bottomLeft);
        int b = rec(sea,{mid_x,topRight[1]},{bottomLeft[0],mid_y + 1});
        int c = rec(sea,topRight,{mid_x + 1,mid_y + 1});
        int d = rec(sea,{topRight[0],mid_y},{mid_x + 1,bottomLeft[1]});

        return a+b+c+d;
    }

public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        return rec(sea,topRight,bottomLeft);
    }
};
