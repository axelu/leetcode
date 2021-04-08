
// 657. Robot Return to Origin
// https://leetcode.com/problems/robot-return-to-origin/



class Solution {
public:
    bool judgeCircle(string& moves) {
        int x = 0, y = 0;
        for(int i = 0; i < moves.size(); ++i) {
            if( moves[i] == 'U' )
                ++y;
            else if( moves[i] == 'D' )
                --y;
            else if( moves[i] == 'L' )
                ++x;
            else
                --x;
        }
        return x == 0 && y == 0;
    }
};
