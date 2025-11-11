
// 3702. Longest Subsequence With Non-Zero Bitwise XOR
// https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/



class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();

        // our answer is either n or n-1 or 0

        int non_zero_count = 0;
        int _xor = 0;
        for(int x: nums) {
            if( x > 0 )
                ++non_zero_count;
            _xor ^= x;
        }


        if( non_zero_count == 0 )
            return 0;


        return _xor != 0 ? n : n-1;
    }
};
