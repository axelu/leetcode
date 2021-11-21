
// 1832. Check if the Sentence Is Pangram
// https://leetcode.com/problems/check-if-the-sentence-is-pangram/


class Solution {
public:
    bool checkIfPangram(string sentence) {
        int cnt[26];memset(cnt,0,sizeof cnt);
        int i;
        for(i = 0; i < sentence.size(); ++i)
            ++cnt[sentence[i]-'a'];
        for(i = 0; i < 26; ++i)
            if( cnt[i] == 0 ) return false;
        return true;
    }
};
