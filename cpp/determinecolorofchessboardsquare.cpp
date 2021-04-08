
// 1812. Determine Color of Chessboard Square
// https://leetcode.com/problems/determine-color-of-a-chessboard-square/


class Solution {
public:
    bool squareIsWhite(string coordinates) {
        //   r   c  letter is r, number is c
        //   e   e  b
        //   e   o  w
        //   o   e  w
        //   o   o  b
        int r = coordinates[0]-'a'+1;
        int c = coordinates[1];
        if( r%2==0 && c%2==0 ) return false;
        else if( r%2==0 && c%2==1 ) return true;
        else if( r%2==1 && c%2==0 ) return true;
        else return false;
    }
};
