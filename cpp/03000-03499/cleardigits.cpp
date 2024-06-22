
// 3174. Clear Digits
// https://leetcode.com/problems/clear-digits/




class Solution {
public:
    string clearDigits(string s) {
        // s consists only of lowercase English letters and digits.
        // The input is generated such that it is possible to delete all digits.

        int n = s.size();
        if( n == 1 )
            return s;

        stack<char> stck;
        for(int i = 0; i < n; ++i) {
            if( isdigit(s[i]) )
                stck.pop();
            else
                stck.push(s[i]);
        }

        string ans = "";
        while( !stck.empty() ) {
            ans.push_back(stck.top());
            stck.pop();
        }
        reverse(ans.begin(),ans.end());

        return ans;
    }
};
