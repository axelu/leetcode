
// 1941. Check if All Characters Have Equal Number of Occurrences
// https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/




class Solution {
public:
    bool areOccurrencesEqual(string s) {
        int cnt[26];memset(cnt,0,sizeof cnt);

        for(int i = 0; i < s.size(); ++i)
            ++cnt[s[i]-'a'];

        int target = -1;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i] != 0 && target == -1 ) {
                target = cnt[i];
                continue;
            }
            if( cnt[i] != 0 && cnt[i] != target )
                return false;
        }


        return true;
    }
};
