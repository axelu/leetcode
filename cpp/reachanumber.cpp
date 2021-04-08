
// 754. Reach a Number
// https://leetcode.com/problems/reach-a-number/
// day 28 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3583/

class Solution {
public:
    int reachNumber(int target) {
        // base case
        if( target == 0 ) return 0;

        // the axis is symetric, so if target < 0, it does not matter for the answer
        target = abs(target);

        // there are two cases:
        // case 1: go to the right and reach the goal -> we are done
        // case 2: go over the target
        //           if over by odd number: keep going until yover by even number
        //           if over by even number: choose one of the steps that goes right to go left
        //                                   the step is the half of we are over
        int ans = 1, sum = 0;
        while(sum < target || (sum - target) % 2 == 1) {
            sum += ans;
            ++ans;
        }
        return ans - 1;
    }
};
