
// 1486. XOR Operation in an Array
// https://leetcode.com/problems/xor-operation-in-an-array/


class Solution {
public:
    int xorOperation(int n, int start) {

        int r = 0;
        for(int i = 0; i < n; ++i) {
            int k = start + 2 * i;
            r ^= k;
        }

        return r;
    }
};
