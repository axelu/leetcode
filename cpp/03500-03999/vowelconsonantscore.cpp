
// 3813. Vowel-Consonant Score
// https://leetcode.com/problems/vowel-consonant-score/



class Solution {
private:
    bool isvowel(char c) {
        if( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' )
            return true;
        return false;
    }
public:
    int vowelConsonantScore(string s) {
        int n = s.size(); // 1 <= n <= 100
        // vowels 'a', 'e', 'i', 'o', or 'u'

        int v = 0, c = 0;
        for(char chr: s)
            if( islower(chr) )
                if( isvowel(chr) )
                    ++v;
                else
                    ++c;

        return c > 0 ? v/c : 0;
    }
};
