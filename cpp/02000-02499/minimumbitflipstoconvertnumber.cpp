
// 2220. Minimum Bit Flips to Convert Number
// https://leetcode.com/problems/minimum-bit-flips-to-convert-number/



class Solution {
public:
    int minBitFlips(int start, int goal) {
        int cnt = 0;

        for(int i = 0; i < 30; ++i)
            if( ((start>>i)&1) != ((goal>>i)&1) )
                ++cnt;

        return cnt;
    }
};
