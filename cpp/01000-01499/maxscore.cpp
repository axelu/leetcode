
// 1422. Maximum Score After Splitting a String
// https://leetcode.com/problems/maximum-score-after-splitting-a-string/



class Solution {
public:
    int maxScore(string s) {
        int total1 = 0;
        for(char ch : s) if( ch == '1' ) ++total1;

        int r = 0;

        int zeros = 0;
        int ones = 0;
        auto n = s.size();
        for(int i = 0; i < n - 1; ++i) {
            if( s[i] == '0' ) {
                ++zeros;
            } else {
                ++ones;
            }
            r = max(r,zeros+(total1-ones));
        }

        return r;
    }
};
