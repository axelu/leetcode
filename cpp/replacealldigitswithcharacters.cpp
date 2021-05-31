
// 1844. Replace All Digits with Characters
// https://leetcode.com/problems/replace-all-digits-with-characters/



class Solution {
public:
    string replaceDigits(string& s) {
        for(int i = 0; i < s.size(); ++i)
            if( i % 2 == 1 )
                s[i] = s[i-1]+(int)(s[i]-'0');
        return s;
    }
};
