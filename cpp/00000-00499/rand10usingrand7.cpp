
// 470. Implement Rand10() Using Rand7()
// day 28 August 2020 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/552/week-4-august-22nd-august-28th/3439/
// https://leetcode.com/problems/implement-rand10-using-rand7/





// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {

        int row = 0;
        int col = 0;

        int idx = 41;
        while(idx > 40) {
            row = rand7();
            col = rand7();
            idx = col + (row - 1) * 7;
        }

        return 1 + (idx - 1) % 10;
    }
};
