
// 1544. Make the String Great
// https://leetcode.com/problems/make-the-string-great/


class Solution {
public:
    string makeGood(string& s) {
        if( s.size() == 1 ) return s;

        for(auto it = s.begin() + 1; it != s.end(); ++it) {
            if( it - s.begin() == 0 ) continue;
            if( abs( *(it - 1) - *it ) == 32 ) {
                it = s.erase(it);
                it = s.erase(it - 1);
                --it;
            }
        }

        return s;
    }
};
