
// 1401. Circle and Rectangle Overlapping
// https://leetcode.com/problems/circle-and-rectangle-overlapping/




class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // x1, y1 coordinates of the bottom-left corner
        // x1, y2 coordinates of the top-left corner
        // x2, y2 coordinates of the top-right corner
        // x2, y1 coordinates of the bottom-right corner

        // shift so everything becomes positive
        int offset = 12000;
        xCenter += offset;
        yCenter += offset;
        x1 += offset;
        y1 += offset;
        x2 += offset;
        y2 += offset;

        // let d be the distances of a corner to the center
        // if d <= radius, then true
        int r2 = radius * radius;
        int d2 = (xCenter - x1)*(xCenter - x1) + (yCenter - y1)*(yCenter - y1);
        if( d2 <= r2 )
            return true;
        d2 = (xCenter - x1)*(xCenter - x1) + (yCenter - y2)*(yCenter - y2);
        if( d2 <= r2 )
            return true;
        d2 = (xCenter - x2)*(xCenter - x2) + (yCenter - y2)*(yCenter - y2);
        if( d2 <= r2 )
            return true;
        d2 = (xCenter - x2)*(xCenter - x2) + (yCenter - y1)*(yCenter - y1);
        if( d2 <= r2 )
            return true;

        // then it could be that the rectangle eclipses the circle
        if( x1 < xCenter && x2 > xCenter &&
            y1 < yCenter && y2 > yCenter ) {

            return true;
        }

        // next if could be that a line of the rectangle runs through the circle
        // horizontal
        if( x1 < xCenter && x2 > xCenter &&
            ( (y1  >= yCenter - radius &&  y1  <= yCenter + radius ) ||
              (y2  >= yCenter - radius &&  y2  <= yCenter + radius ) ) ) {

            return true;
        }

        // vertical
        if( y1 < yCenter && y2 > yCenter &&
            ( (x1  >= xCenter - radius &&  x1  <= xCenter + radius ) ||
              (x2  >= xCenter - radius &&  x2  <= xCenter + radius ) ) ) {

            return true;
        }

        return false;
    }
};
