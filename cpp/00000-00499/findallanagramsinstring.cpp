
// 438. Find All Anagrams in a String
// https://leetcode.com/problems/find-all-anagrams-in-a-string/




class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        size_t ssz = s.size();
        if( ssz == 0 ) return {};
        size_t psz = p.size(); // constraint: p is non-empty
        if( ssz < psz ) return {};

        array<int,26> pchs{0}; // count frequency of chars in string p
        for(int i = 0; i < psz; ++i)
            ++pchs[p[i]-'a'];

        vector<int> ans;
        array<int,26> schs{0}; // count frequency of chars in string s that are 'in view'
        for(int i = 0; i < ssz; i ++) {
            // add the char in s that came into view
            ++schs[s[i]-'a'];

            // subtract the char in s that fell 'out of view'
            if( i >= psz )
                --schs[s[i-psz]-'a'];

            // if the same number per char, then it is a start index for an anagram
            if( pchs == schs )
                ans.push_back(i-psz+1);
        }

        return ans;
    }
};
