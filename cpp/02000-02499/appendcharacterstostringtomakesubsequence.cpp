
// 2486. Append Characters to String to Make Subsequence
// https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/



class Solution {
public:
    int appendCharacters(string s, string t) {
        int s_sz = s.size();
        int i = 0; // index in s
        int t_sz = t.size();
        int j = 0; // index in t

        for(; j < t_sz; ++j) {

            for(; i < s_sz; ++i) {
                if( s[i] == t[j] )
                    break;
            }
            if( i == s_sz )
                break;
            else
                ++i;
        }

        return t_sz - j;
    }
};
