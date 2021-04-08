
// Shuffle String
// https://leetcode.com/problems/shuffle-string/

class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        auto n = s.size();
        if( n == 1 ) return s;

        string r = s;
        for(int i = 0; i < n; ++i) {
            if( indices[i] == i ) continue;
            r.replace(indices[i],1,1,s[i]);
            // cout << r << endl;
        }

        return r;
    }
};
