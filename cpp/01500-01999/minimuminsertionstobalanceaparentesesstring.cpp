
// 1541. Minimum Insertions to Balance a Parentheses String
// https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/



class Solution {
public:
    int minInsertions(string s) {

        int expect = 0;
        int cnt = 0;

        int n = s.size();
        for(int i = 0; i < n; ++i) {
            if( s[i] == '(' ) {
                ++expect;
            } else {
                // closing parentheses come in two's
                // hence peek ahead
                if( i+1 < n && s[i+1] == ')' ) {
                    // we have a pair of closing parentheses
                    ++i;
                } else {
                    // we do NOT have a proper pair of closing parentheses
                    // we would need to add a closing parenthesis
                    ++cnt;
                }
                // we need to consume an opening parenthesis
                if( expect == 0 )
                    ++cnt;
                else
                    --expect;
            }
        }
        // finish up
        cnt += 2*expect;

        return cnt;
    }
};
