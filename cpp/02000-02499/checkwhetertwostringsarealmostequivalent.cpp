
// 2068. Check Whether Two Strings are Almost Equivalent
// https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent/



class Solution {
public:
    bool checkAlmostEquivalent(string word1, string word2) {
        int n = word1.size(); // n == word1.size() == word2.size()

        int cnt1[26];memset(cnt1,0,sizeof cnt1);
        int cnt2[26];memset(cnt2,0,sizeof cnt2);
        for(int i = 0; i < n; ++i) {
            ++cnt1[word1[i]-'a'];
            ++cnt2[word2[i]-'a'];
        }

        for(int i = 0; i < 26; ++i)
            if( abs(cnt1[i]-cnt2[i]) > 3 )
                return false;

        return true;
    }
};
