
// 1010. Pairs of Songs With Total Durations Divisible by 60
// https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/
// day 8 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/570/week-2-december-8th-december-14th/3559/


class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        size_t n = time.size();
        if( n == 1 ) return 0;

        int rs[60000];
        rs[1] = 1;
        for(int i = 2; i < n; ++i)
            rs[i] = rs[i-1] + i;

        int a[60]; memset(a,0,sizeof a);
        for(int i = 0; i < n; ++i)
            ++a[time[i] % 60];

        int r = 0;
        if( a[0] > 1 ) r += rs[a[0]-1];
        if( a[30] > 1 ) r += rs[a[30]-1];
        for(int i = 1; i < 30; ++i)
            r += a[i]*a[60-i];
        return r;
    }
};
