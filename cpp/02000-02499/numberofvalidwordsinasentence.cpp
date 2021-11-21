
// 2047. Number of Valid Words in a Sentence
// https://leetcode.com/problems/number-of-valid-words-in-a-sentence/



class Solution {
private:
    bool isValidWord(string& s) {
        // cout << "isValidWord s::" << s << "::" << endl;
        int n = s.size();

        int hyphens = 0;
        char c;
        for(int i = 0; i < n; ++i) {
            c = s[i];

            if( isdigit(c) ) {
                return false;
            } else if( c == '-' ) {
                if( i == 0 || i == n-1 )
                    return false;
                if( !islower(s[i-1]) || !islower(s[i+1]) )
                    return false;
                if( hyphens == 1 )
                    return false;
                ++hyphens;
            } else if( c == '!' || c == '.' || c == ',' ) {
                if( i != n-1 )
                    return false;
            } else if( !islower(c) ) {
                return false;
            }
        }
        return true;
    }
public:
    int countValidWords(string sentence) {
        int n = sentence.size();

        int ans = 0;
        string s = "";
        char c;
        for(int i = 0; i < n; ++i) {
            c = sentence[i];
            if( c == ' ' ) {
                if( !s.empty() ) {
                    if( isValidWord(s) )
                        ++ans;
                    s = "";
                }
            } else {
                s = s + c;
            }
        }
        // finish up
        if( !s.empty() && isValidWord(s) )
            ++ans;

        return ans;
    }
};
