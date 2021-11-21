
// 1217. Minimum Cost to Move Chips to The Same Position
// https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/



class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int cntEven = 0;
        int cntOdd = 0;
        for(int i : position) {
            if( i % 2 == 0 ) {
                cntEven++;
            } else {
                cntOdd++;
            }
        }
        return min(cntOdd, cntEven);
    }
};
