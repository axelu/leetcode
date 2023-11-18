
// 2849. Determine if a Cell Is Reachable at a Given Time
// https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/





class Solution {
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        // edge case
        if( sx == fx && sy == fy ) {
            // start and finish are the same,
            // we cannot make t == 1 happen
            return t != 1;
        }



        int dx = abs(sx-fx);
        int dy = abs(sy-fy);

        int fastest = min(dx,dy) + (max(dx,dy)-min(dx,dy));

        return fastest <= t;
    }
};
