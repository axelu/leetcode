
// 3298. Count Substrings That Can Be Rearranged to Contain a String II
// https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/


// sanme solution as 
// https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/



class Solution {
public:
    long long validSubstringCount(string word1, string word2) {

        int refcnt[26];memset(refcnt,0,sizeof refcnt);
        for(char c: word2)
            ++refcnt[c-'a'];

        // sliding window
        int missing = 0;
        for(int i = 0; i < 26; ++i)
            if( refcnt[i] != 0 )
                ++missing;

        long long ans = 0LL;

        int cnt[26]; memset(cnt,0,sizeof cnt);
        int n = word1.size();
        int i = 0;
        for(int j = 0; j < n; ++j) {
            int c = word1[j] - 'a';

            // we are only interested in chars that occur in word2
            if( refcnt[c] != 0 ) {
                ++cnt[c];
                if( cnt[c] == refcnt[c] ) {
                    // we have collected enough of char c
                    --missing;

                    if( missing == 0 ) {
                        // we have enough of all chars in word2
                        // we can form n-j substrings
                        ans += (long long)(n-j);

                        // shrink our window
                        while( i <= j ) {
                            // we are only interested in chars that occur in word2
                            if( refcnt[word1[i]-'a'] != 0  ) {
                                --cnt[word1[i]-'a'];
                                if( cnt[word1[i]-'a'] < refcnt[word1[i]-'a'] ) {
                                    ++missing;
                                    ++i;
                                    break;
                                } else {
                                    // if we take the current char at i away, we still meet the criteria
                                    ans += (long long)(n-j);
                                }
                            } else {
                                // if we take the current char at i away, we still meet the criteria
                                ans += (long long)(n-j);
                            }
                            ++i;
                        }
                    }
                }
            }

        }

        return ans;

    }
};
