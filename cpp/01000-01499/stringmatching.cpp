
// 1408. String Matching in an Array
// https://leetcode.com/problems/string-matching-in-an-array/


class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        auto n = words.size();
        vector<string> r = {};
        if( n == 1 ) return r;

        string a = "";
        int i = 0;
        int j = 0;
        vector<bool> added(n,false);
        for(; i < n; ++i) {
            a = words[i];
            j = 0;
            for(; j < n; ++j) {
                if( i == j ) continue;
                if( a.find(words[j]) != string::npos && !added[j] ) {
                    r.push_back(words[j]);
                    added[j] = true;
                }
            }
        }

        return r;
    }
};
