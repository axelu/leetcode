
// day 7 September 2020 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/554/week-1-september-1st-september-7th/3451/
// https://leetcode.com/problems/word-pattern/


class Solution {
public:
    bool wordPattern(string pattern, string str) {
        if( pattern.empty() || str.empty() ) return false;
        if( str.find_first_of("abcdefghijklmnopqrstuvwxyz") == string::npos ) return false;

        int pos = 0;
        unordered_map<char,string> m; // keyed by char in pattern
        unordered_map<string,char> n; // keyed by word in str

        for(char c : pattern) {

            // cout << "char in pattern: " << c << endl;

            // get word in string
            if( pos == str.size() ) return false;
            bool ws = false;
            string word = "";
            string ss = str.substr(pos);
            for (char wc : ss) {
                ++pos;
                if( wc == ' ' ) {
                    if ( ws ) break;
                } else {
                    ws = true;
                    word = word + wc;
                }
            }

            // cout << "word in str: " << word << endl;

            // check pattern to word
            auto p = m.find(c);
            if( p != m.end() ) {
                if( p->second != word ) return false;
            } else {
                m.insert({c,word});
            }

            // check word to pattern
            auto q = n.find(word);
            if( q != n.end() ) {
                if( q->second != c ) return false;
            } else {
                n.insert({word,c});
            }
        }

        // cout << "pos " << pos << endl;
        // cout << "string remainder: |" << str.substr(pos) << "|" << endl;
        return ( str.substr(pos - 1,1) == " " ) ? false : true;
    }
};
