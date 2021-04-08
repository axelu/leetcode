
// 1796. Second Largest Digit in a String
// https://leetcode.com/problems/second-largest-digit-in-a-string/




class Solution {
public:
    int secondHighest(string s) {
        int n = s.size();

        int digits[10]; memset(digits,0,sizeof digits);

        int i;
        for(i = 0; i < n; ++i) {
            if( isdigit(s[i]) ) {
                ++digits[s[i]- '0'];
            }
        }

        int mx = -1;
        for(i = 9; i >= 0; --i) {
            if( digits[i] != 0 ) {
                if( mx == -1 ) {
                    mx = i;
                } else {
                    return i;
                }
            }
        }
        return -1;
    }
};
