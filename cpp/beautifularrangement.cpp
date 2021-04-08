
// 526. Beautiful Arrangement
// https://leetcode.com/problems/beautiful-arrangement/
// day 3 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/579/week-1-january-1st-january-7th/3591/


class Solution {
private:
    int N;
    int used[16];
    int ans;

    void rec(int i) {
        if( i == N+1 ) {
            ++ans;
            return;
        }

        for(int k = 1; k <= N; ++k) {
            if( used[k] ) continue;
            if( k % i == 0 || i % k == 0 ) {
                used[k] = 1;
                rec(i+1);
                used[k] = 0;
            }
        }
    }
public:
    int countArrangement(int n) {
        N = n;
        memset(used,0,sizeof used);
        ans = 0;

        // position 1
        for(int k = 1; k <= n; ++k) {
            used[k] = 1;
            rec(2);
            used[k] = 0;
        }

        return ans;
    }
};
