#include <iostream>
#include <cassert>

#include <string>
#include <vector>

// 14. Longest Common Prefix
// https://leetcode.com/problems/longest-common-prefix/

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        if ( strs.empty() ) return "";
        if ( strs.size() == 1 ) return strs[0];

        string r = strs[0];
        if ( r == "" ) return "";
        for (auto itstrs = strs.begin() + 1; itstrs != strs.end(); ++itstrs) {
            // debug
            // cout << *itstrs << endl;

            // if ( r.size() > itstrs->size() ) r = r.substr(0, itstrs->size());
            if ( r.size() > itstrs->size() ) r.erase(itstrs->size());
            // debug
            // cout << r << endl;

            string::iterator itr = r.begin();
            string::iterator itw = itstrs->begin();
            while ( itr != r.end() ) {
                if ( *itr != *itw ) break;
                itr++;
                itw++;
            }
            if ( itr == r.begin() ) return "";
            // if ( itr != r.end() ) r = r.substr(0, itr - r.begin());
            if ( itr != r.end() ) r.erase(itr - r.begin());

        }
        // debug
        // cout << r << endl;
        return r;
    }
};

int main() {

    Solution s;

    vector<string> v0;
    assert(s.longestCommonPrefix(v0) == "");

    vector<string> v1 = {"flower"};
    assert(s.longestCommonPrefix(v1) == "flower");

    vector<string> v2 = {"flower","flow","flight"};
    assert(s.longestCommonPrefix(v2) == "fl");

    vector<string> v3 = {"dog","racecar","car"};
    assert(s.longestCommonPrefix(v3) == "");



    return 0;
}
