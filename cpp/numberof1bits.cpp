
// Number of 1 bits
// https://leetcode.com/problems/number-of-1-bits/


class Solution {
public:
    int hammingWeight(uint32_t n) {
        string b = bitset<32>(n).to_string();
        return count_if(begin(b), end(b),[](char c){return c == '1';});
    }
};
