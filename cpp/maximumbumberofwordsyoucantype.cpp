
// 1935. Maximum Number of Words You Can Type
// https://leetcode.com/problems/maximum-number-of-words-you-can-type/
// https://leetcode.com/contest/weekly-contest-250/problems/maximum-number-of-words-you-can-type/





class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        int f[26];memset(f,0,sizeof f);
        for(char c : brokenLetters)
            f[c-'a'] = 1;

        int ans = 0;

        int n = text.size();
        bool canType = true;
        for(int i = 0; i < n; ++i) {

            if( text[i] != ' ' && canType )
                if( f[text[i]-'a'] )
                    canType = false;

            if( text[i] == ' ' || i == n-1 ) {
                if( canType )
                    ++ans;
                canType = true;
            }
        }

        return ans;
    }
};
