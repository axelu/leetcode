
// 1153. String Transforms Into Another String
// https://leetcode.com/problems/string-transforms-into-another-string/



// see solution on leetcode

class Solution {
public:
    bool canConvert(string str1, string str2) {
        // base case
        if (str1 == str2)
            return true;

        int mapping[26];memset(mapping,-1,sizeof mapping);
        int charsInStr2[26];memset(charsInStr2,0,sizeof charsInStr2);

        // a given char in str1 can only be mapped to on char in str2
        for(int i = 0; i < str1.size(); ++i) {
            if( mapping[str1[i]-'a'] == -1 ) {
                mapping[str1[i]-'a'] = str2[i]-'a';
                charsInStr2[str2[i]-'a'] = 1;
            } else if ( mapping[str1[i]-'a'] != str2[i]-'a' ) {
                // char maps to 2 different chars
                return false;
            }
        }

        // we must have at least one temporary char
        // that can be used to break any loops
        int cnt = 0; // unique chars in str2
        for(int i = 0; i < 26; ++i)
            if( charsInStr2[i] )
                ++cnt;
        if( cnt < 26 )
            return true;

        return false;
    }
};
