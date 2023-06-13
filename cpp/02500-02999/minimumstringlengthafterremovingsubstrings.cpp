
// 2696. Minimum String Length After Removing Substrings
// https://leetcode.com/problems/minimum-string-length-after-removing-substrings/




class Solution {
public:
    int minLength(string s) {

        int i = 0;
        while( s.size() > 0 && i != s.size() - 1 ) {

            if( (s[i] == 'A' && s[i+1] == 'B') ||
                (s[i] == 'C' && s[i+1] == 'D') ) {

                s.erase(i,2);
                --i;
                i = max(0,i);
                continue;
            }

            ++i;
        }

        return s.size();
    }
};
