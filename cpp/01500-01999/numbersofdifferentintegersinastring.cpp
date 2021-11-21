
// 1805. Number of Different Integers in a String
// https://leetcode.com/problems/number-of-different-integers-in-a-string/


class Solution {
private:
    void trimLeadingZeros(string& s) {
        while( !s.empty() && s[0] == '0' ) {
            if( s.size() == 1 ) break;
            s.erase(0,1);
        }
    }
public:
    int numDifferentIntegers(string word) {
        int n = word.size(); // 1 <= word.length <= 1000

        unordered_set<string> us;
        string nbr = "";
        for(int i = 0; i < n; ++i) {
            if( isalpha(word[i]) ) {
                if( !nbr.empty() ) {
                    trimLeadingZeros(nbr);
                    us.insert(nbr);
                    nbr = "";
                }
            } else {
                nbr += word[i];
            }
        }
        if( !nbr.empty() ) {
            trimLeadingZeros(nbr);
            us.insert(nbr);
        }
        return us.size();
    }
};
