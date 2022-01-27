
// 600. Non-negative Integers without Consecutive Ones
// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/
// day 25 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/611/week-4-july-22nd-july-28th/3826/




// two approaches I have looked at in detail
// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/discuss/295762/C%2B%2B-O(logN)-Simple-Math
// I was going down a similar approach as above
// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/discuss/103768/C%2B%2B-DP-dfs-and-Memozied


// solution approach #3

class Solution {
public:
    int findIntegers(int n) {
        int f[32];
        f[0] = 1;
        f[1] = 2;
        for(int i = 2; i < 32; ++i)
            f[i] = f[i-1] + f[i-2];

        int i = 30, sum = 0, prev_bit = 0;
        while(i >= 0) {
            if( (n & (1 << i)) != 0 ) {
                sum += f[i];
                if( prev_bit == 1 ) {
                    sum--;
                    break;
                }
                prev_bit = 1;
            } else
                prev_bit = 0;
            i--;
        }
        return sum + 1;
    }
};
