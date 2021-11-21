
// 1657. Determine if Two Strings Are Close
// https://leetcode.com/problems/determine-if-two-strings-are-close/


class Solution {
public:
    bool closeStrings(string word1, string word2) {
        auto n = word1.size(); // 1 <= word1.length, word2.length <= 10e5
        if( n != word2.size() ) return false;
        if( n == 1 )
            return word1 == word2 ? true : false;

        // frequencies of a given char in word1 and word2
        int a[26]; memset(a,0,sizeof a);
        int b[26]; memset(b,0,sizeof b);
        for(int i = 0; i < n; ++i) {
            ++a[word1[i]-'a'];
            ++b[word2[i]-'a'];
        }

        unordered_map<int,int> um1;
        unordered_map<int,int> um2;
        int f;
        pair<unordered_map<int,int>::iterator,bool> p;
        for(int i = 0; i < 26; ++i) {
            // do we have the same letter as operations require existing letter only
            if( (a[i] == 0 && b[i] != 0) || (a[i] != 0 && b[i] == 0) ) return false;
            // word1
            f = a[i];
            if( f != 0 ) {
                p = um1.insert({f,1});
                if( !p.second )
                    ++p.first->second;
            }
            // word2
            f = b[i];
            if( f != 0 ) {
                p = um2.insert({f,1});
                if( !p.second )
                    ++p.first->second;
            }
        }

        // having the same frequencies the same number of times is the other pre-requisite
        return um1 == um2;
    }
};
