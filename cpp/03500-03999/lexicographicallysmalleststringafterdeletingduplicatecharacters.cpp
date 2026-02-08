
// 3816. Lexicographically Smallest String After Deleting Duplicate Characters
// https://leetcode.com/problems/lexicographically-smallest-string-after-deleting-duplicate-characters/



class Solution {
public:
    string lexSmallestAfterDeletion(string s) {
        // count freq of chars
        // go left to right
        // delete a char if count >= 2 AND curchar > nextchar
        // chop the tail as long as charcount >= 2

        int cnt[26]; memset(cnt,0,sizeof cnt);
        for(char c: s)
            ++cnt[c-'a'];

        for(auto it = s.begin(); it != s.end(); ) {
            // cout << s << endl;
            if( next(it) != s.end() ) {
                char curchar = *it;
                char nxtchar = *next(it);
                if( curchar > nxtchar && cnt[curchar-'a'] > 1 ) {
                    --cnt[curchar-'a'];
                    it = s.erase(it);
                    if( it != s.begin() )
                        --it;
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        }

        while( cnt[s.back()-'a'] > 1 ) {
            --cnt[s.back()-'a'];
            s.pop_back();
        }

        return s;
    }
};
