
// 3274. Check if Two Chessboard Squares Have the Same Color
// https://leetcode.com/problems/check-if-two-chessboard-squares-have-the-same-color/




class Solution {
private:
    char get_color(string coordinate) {
        int col = coordinate[0] - 'a';
        int row = coordinate[1] - '0';

        if( row % 2 == 1 && col % 2 == 1 )
            return 'w';
        else if( row % 2 == 1 && col % 2 == 0 )
            return 'b';
        else if( row % 2 == 0 && col % 2 == 0 )
            return 'w';
        else // ( row % 2 == 0 && col % 2 == 1 )
            return 'b';
    }

public:
    bool checkTwoChessboards(string coordinate1, string coordinate2) {
        return get_color(coordinate1) == get_color(coordinate2);
    }
};
