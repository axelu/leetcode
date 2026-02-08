
// 3760. Maximum Substrings With Distinct Start
// https://leetcode.com/problems/maximum-substrings-with-distinct-start/



class Solution {
public:
    int maxDistinct(string s) {
        int cnt = 0;
        bool seen[26];memset(seen,false,sizeof seen);
        for(char c: s) {
            if( !seen[c-'a'] )
                ++cnt;
            seen[c-'a'] = true;
        }
        return cnt;
    }
};
