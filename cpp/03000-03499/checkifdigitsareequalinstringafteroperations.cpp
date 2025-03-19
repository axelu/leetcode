
// 3461. Check If Digits Are Equal in String After Operations I
// https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i/



class Solution {
public:
    bool hasSameDigits(string s) {
        int n = s.size();

        // brute force
        while( n > 2 ) {
            string t = "";
            for(int i = 0; i < n-1; ++i) {
                int a = ((int)(s[i]-'0') + (int)(s[i+1]-'0')) % 10;
                t.push_back(a+'0');
            }
            swap(s,t);
            n = s.size();
        }

        return s[0] == s[1];
    }
};
