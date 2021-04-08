
// 242. Valid Anagram
// https://leetcode.com/problems/valid-anagram/



class Solution {
public:
    bool isAnagram(string s, string t) {
        size_t ssz = s.size();
        size_t tsz = t.size();
        if( ssz != tsz ) return false;
        if( 0 == ssz ) return true;

        array<int,26> schs{0}; // count frequency of chars in string s
        array<int,26> tchs{0}; // count frequency of chars in string t
        for(int i = 0; i < ssz; ++i) {
            ++schs[s[i]-'a'];
            ++tchs[t[i]-'a'];
        }

        return schs == tchs;
    }
};
