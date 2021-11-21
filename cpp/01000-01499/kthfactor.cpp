
// 1492. The kth Factor of n
// https://leetcode.com/problems/the-kth-factor-of-n/
// day 4 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/569/week-1-december-1st-december-7th/3554/



class Solution {
public:
    int kthFactor(int n, int k) {

        int j = 0;
        for(int i = 1; i <= n; ++i) {
            if( n % i == 0 ) {
                ++j;
                if( j  == k )
                    return i;
            }
        }

        return -1;
    }
};
