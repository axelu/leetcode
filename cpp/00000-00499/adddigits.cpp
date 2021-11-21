
// 258. Add Digits
// https://leetcode.com/problems/add-digits/



class Solution {
public:
    int addDigits(int num) {
        // math: Digital Root
        return num == 0 ? 0 : 1 + (num - 1) % 9;
    }
};
