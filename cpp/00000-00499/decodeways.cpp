
// 91. Decode Ways
// https://leetcode.com/problems/decode-ways/
// day 26 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3581/


/*
A -> 1, B -> 2, ... Z -> 26
ABCDEFGHIJKLMNOPQRSTUVWXYZ
if there is a zero that is not part of either a 20 or a 30 than result is invalid, return 0
10 T only
11 AA or K
19 AI or S
20 T only
21 BA or U
26 BF or Z
27 BG only

30 not valid, result 0

163 -> 2
AFC or PC

226 -> 3
BBF,BZ or VF

2262
226 2
"BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6) * B = 3 * 1 = 3
+
22 62
BB (2 2), V (22) * FB (6 2) = 2 * 1 = 2 but it is the same
+
2 262
B (2) * BFB (2 6 2), ZB (26 2) = 1 * 2 but it is the same
*/
class Solution {
public:
    int numDecodings(string s) {
        size_t n = s.size();
        if( n == 0 ) return 0;
        // leading zero's is invalid
        if( s[0] == '0' ) return 0;

        int mem[n+1]; memset(mem,0,sizeof mem);
        mem[0] = 1;
        mem[1] = 1;
        for(int i = 2; i <= n; ++i) {
            if( '1' <= s[i-1] && s[i-1] <= '9' ) mem[i] = mem[i-1];
            if(s[i-2] == '1') {
                mem[i] += mem[i-2];
            } else if( s[i-2] == '2' && '0' <= s[i-1] && s[i-1] <= '6' ) {
                mem[i] += mem[i-2];
            }
        }
        return mem[n];
    }
};
