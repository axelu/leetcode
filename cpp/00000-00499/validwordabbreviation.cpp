
// 408. Valid Word Abbreveation
// https://leetcode.com/problems/valid-word-abbreviation/



class Solution {
public:
    bool validWordAbbreviation(string& s, string& abbr) {
        int m = abbr.size();
        int n = s.size();

        string dist = "";
        int d, j = 0;
        for(int i = 0; i < m; ++i) {
            if( isdigit(abbr[i]) ) {
                if( dist.empty() && abbr[i] == '0' ) return false;
                dist = dist + abbr[i];
                continue;
            }
            if( !dist.empty() ) {
                d = stoi(dist);
                j += d;
                dist = "";
            }
            if( j >= n )
                return false;
            if( s[j] != abbr[i] )
                return false;
            ++j;
        }
        // finish up
        if( !dist.empty() ) {
            d = stoi(dist);
            j += d;
            dist = "";
        }
        return j == n;
    }
};
