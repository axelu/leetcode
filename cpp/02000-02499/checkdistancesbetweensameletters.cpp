
// 2399. Check Distances Between Same Letters
// https://leetcode.com/problems/check-distances-between-same-letters/



class Solution {
public:
    bool checkDistances(string s, vector<int>& distance) {
        int d[26];memset(d,-1,sizeof d);
        for(int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if( d[c] == - 1 ) {
                // this is the 1st time we see this char,
                // so we record the current index
                d[c] = i;
            } else {
                // this is the 2nd time we see this char,
                // so lets record the 'distance'
                d[c] = i - d[c] - 1;
            }
        }

        for(int i = 0; i < 26; ++i) {
            if( d[i] == -1 )
                continue;
            if( d[i] != distance[i] )
                return false;
        }

        return true;
    }
};
