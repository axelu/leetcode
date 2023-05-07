
// 2139. Minimum Moves to Reach Target Score
// https://leetcode.com/problems/minimum-moves-to-reach-target-score/





class Solution {
public:
    int minMoves(int target, int maxDoubles) {
        int steps = 0;

        while( target > 1 ) {

            if( maxDoubles == 0 ) {
                // we just need to decrement by 1
                steps += target - 1;
                target = 1;

            } else if( target % 2 != 0 ) {
                --target;
                ++steps;

            } else {
                target /= 2;
                ++ steps;
                --maxDoubles;
            }
        }

        return steps;
    }
};
