
// 3232. Find if Digit Game Can Be Won
// https://leetcode.com/problems/find-if-digit-game-can-be-won/


class Solution {
public:
    bool canAliceWin(vector<int>& nums) {
        int single_sum = 0;
        int double_sum = 0;
        for(int i: nums)
            if( i < 10 )
                single_sum += i;
            else
                double_sum += i;

        return single_sum != double_sum;
    }
};
