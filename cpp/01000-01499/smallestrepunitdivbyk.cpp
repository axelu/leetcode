
// 1015. Smallest Integer Divisible by K
// https://leetcode.com/problems/smallest-integer-divisible-by-k/
// day 25 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/567/week-4-november-22nd-november-28th/3543/


class Solution {
public:
    int smallestRepunitDivByK(int K) {
        int rem = 0;
        for(int i = 1; i <= K; ++i) {
            rem = (rem * 10 + 1) % K;
            if( rem == 0 ) return i;
        }
        return -1;
    }
};
