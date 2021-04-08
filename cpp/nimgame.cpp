
// 294. Nim Game
// https://leetcode.com/problems/nim-game/


class Solution {
public:
    bool canWinNim(int n) {
        // https://www.cs.umd.edu/~gordon/ysp/nim.pdf
        return (n % 4 != 0);
    }
};
