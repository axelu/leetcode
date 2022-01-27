
// 948. Bag of Tokens
// day 24 October 2020 challenge
// https://leetcode.com/problems/bag-of-tokens/

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int P) {
        auto n = tokens.size();

        sort(begin(tokens), end(tokens));
        int lo = 0;
        int hi = n - 1;
        int r = 0;
        int score = 0;
        while(lo <= hi && (P >= tokens[lo] || score > 0)) {
            while(lo <= hi && P >= tokens[lo]) {
                P -= tokens[lo];
                ++score;
                ++lo;
            }

            r = max(r, score);

            if( lo <= hi && score > 0 ) {
                P += tokens[hi];
                --score;
                --hi;
            }
        }

        return r;
    }
};
