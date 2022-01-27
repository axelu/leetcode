
// 291. Word Pattern II
// https://leetcode.com/problems/word-pattern-ii/



class Solution {
private:
    bool isMapped(string& t, string mapping[]) {
        for(int i = 0; i < 26; ++i)
            if( mapping[i] == t )
                return true;
        return false;
    }

    bool rec(string& pattern, int posP, string& s, int posS, string mapping[]) {
        if( posP == pattern.size() && posS == s.size() )
            return true;

        if( posP == pattern.size() || posS == s.size() )
            return false;

        char c = pattern[posP];
        if( !mapping[c-'a'].empty() ) {
            // char c in pattern already mapped
            int l = mapping[c-'a'].size();
            if( posS + l <= s.size() && s.substr(posS,l) == mapping[c-'a'] ) {
                return rec(pattern,posP+1,s,posS+l,mapping);
            }
        } else {
            // map c to a substring in s
            for(int l = 1; l <= s.size()-(pattern.size()-1); ++l) {
                if( posS+l > s.size() )
                    break;
                string t = s.substr(posS,l);
                if( isMapped(t,mapping) )
                    continue;
                mapping[c-'a'] = t;
                bool f = rec(pattern,posP+1,s,posS+l,mapping);
                if( f )
                    return true;
            }
            // backtrack
            mapping[c-'a'] = "";
        }
        return false;
    }

public:
    bool wordPatternMatch(string pattern, string s) {
        // for simplicity reasons we assume
        // a char in pattern can be mapped to
        // a substring in s of length 1 to s.size()-(pattern.size()-1)

        string mapping[26];
        return rec(pattern,0,s,0,mapping);
    }
};
