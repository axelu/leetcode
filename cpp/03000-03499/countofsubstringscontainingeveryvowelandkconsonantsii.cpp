
// 3306. Count of Substrings Containing Every Vowel and K Consonants II
// https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/







class Solution {
private:
    bool isvowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c ==  'o' || c == 'u';
    }

public:
    long long countOfSubstrings(string word, int k) {
        int n = word.size();

        // for each position in word let us record
        // the next position to its right that contains a consonant

        int next_consonant[n];
        bool vowel[n]; memset(vowel,false,sizeof vowel);

        // from right to left
        int nxt = n;
        for(int i = n-1; i >= 0; --i) {
            next_consonant[i] = nxt;
            if( isvowel(word[i]) )
                vowel[i] = true;
            else
                nxt = i;

        }

        long long ans = 0LL;

        // sliding window

        int cnt[26];memset(cnt,0,sizeof cnt);
        int missingvowels = 5; // there are 5 vowels: a, e, i, o and u
        int consonants = 0;

        int i = 0;
        for(int j = 0; j < n; ++j) {
            int cj = word[j]-'a';

            ++cnt[cj];
            if( vowel[j] && cnt[cj] == 1 )
                --missingvowels;

            // if missing == 0 then
            // we have a substring that contains every vowel at least once

            if( !vowel[j] )
                ++consonants;

            // shrink the window
            while( consonants > k ) {
                int ci = word[i]-'a';
                --cnt[ci];

                if( vowel[i] && cnt[ci] == 0 )
                    ++missingvowels;
                if( !vowel[i] )
                    --consonants;

                ++i;
            }
            while( missingvowels == 0 && consonants == k ) {
                // cout << "i " << i << " j " << j << endl;
                // word[i,j] is a substring that has every vowel at least once and
                // exactly k consonants

                // we can towards the right make substrings still meeting the condition
                long long l = next_consonant[j] - j;
                ans += l;

                int ci = word[i]-'a';
                --cnt[ci];

                if( vowel[i] && cnt[ci] == 0 )
                    ++missingvowels;
                if( !vowel[i] )
                    --consonants;

                ++i;
            }
        }


        return ans;
    }
};
