

// Reverse Bits
// https://leetcode.com/problems/reverse-bits/


class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        string b = bitset<32>(n).to_string();
        reverse(begin(b), end(b));
        return bitset<32>(b).to_ulong();
    }
};
