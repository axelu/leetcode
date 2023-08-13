
// 2531. Make Number of Distinct Characters Equal
// https://leetcode.com/problems/make-number-of-distinct-characters-equal/




class Solution {
public:
    bool isItPossible(string word1, string word2) {

        int chrs1[26];memset(chrs1,0,sizeof chrs1);
        int cnt1 = 0;
        for(char c: word1) {
            ++chrs1[c-'a'];
            if( chrs1[c-'a'] == 1 )
                ++cnt1;
        }

        int chrs2[26];memset(chrs2,0,sizeof chrs2);
        int cnt2 = 0;
        for(char c: word2) {
            ++chrs2[c-'a'];
            if( chrs2[c-'a'] == 1 )
                ++cnt2;
        }

        bool f = false;
        for(int i = 0; i < 26; ++i) {
            if( chrs1[i] == 0 )
                continue;

            --chrs1[i];
            if( chrs1[i] == 0 )
                --cnt1;
            ++chrs2[i];
            if( chrs2[i] == 1 )
                ++cnt2;

            for(int j = 0; j < 26; ++j) {
                if( chrs2[j] == 0 )
                    continue;

                // we cannot move a char from word2 that we didn't have
                if( i == j && chrs2[j] == 1 )
                    continue;

                --chrs2[j];
                if( chrs2[j] == 0 )
                    --cnt2;
                ++chrs1[j];
                if( chrs1[j] == 1 )
                    ++cnt1;

                if( cnt1 == cnt2 )
                    return true;

                // backtrack
                ++chrs2[j];
                if( chrs2[j] == 1 )
                    ++cnt2;
                --chrs1[j];
                if( chrs1[j] == 0 )
                    --cnt1;
            }

            // backtrack
            ++chrs1[i];
            if( chrs1[i] == 1 )
                ++cnt1;
            --chrs2[i];
            if( chrs2[i] == 0 )
                --cnt2;
        }

        return false;
    }
};
