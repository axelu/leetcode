
// 2347. Best Poker Hand
// https://leetcode.com/problems/best-poker-hand/


class Solution {
public:
    string bestHand(vector<int>& ranks, vector<char>& suits) {
        int cnt_ranks[14];memset(cnt_ranks,0,sizeof cnt_ranks);
        int cnt_suits[4];memset(cnt_suits,0,sizeof cnt_suits);
        for(int i = 0; i < 5; ++i) {
            ++cnt_ranks[ranks[i]];
            ++cnt_suits[suits[i]-'a'];
        }

        // best to worst
        // "Flush": Five cards of the same suit.
        for(int i = 0; i < 4; ++i)
            if( cnt_suits[i] == 5 )
                return "Flush";

        int mx_rank = 0;
        for(int i = 1; i < 14; ++i)
            mx_rank = max(mx_rank,cnt_ranks[i]);
        if( mx_rank >= 3 )
            return "Three of a Kind";
        if( mx_rank == 2 )
            return "Pair";

        return "High Card";
    }
};
