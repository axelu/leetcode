
// 165. Compare Version Numbers
// day 9 September 2020 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/555/week-2-september-8th-september-14th/3454/
// https://leetcode.com/problems/compare-version-numbers/



#include <iostream>
#include <cassert>

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int l1 = count(version1.begin(), version1.end(), '.');
        int l2 = count(version2.begin(), version2.end(), '.');
        int l = max(l1,l2) + 1;

        auto v1 = versionToVector(version1, l);
        auto v2 = versionToVector(version2, l);

        auto it2 = v2.begin();
        for(auto it1 = v1.begin(); it1 != v1.end(); ++it1) {
            if( *it1 > *it2 ) {
                return 1;
            } else if ( *it1 < *it2 ) {
                return -1;
            }
            ++it2;
        }

        return 0;
    }
private:
    vector<int> versionToVector(string version, int l) {
        vector<int> r;

        string s = "";
        for(char c : version) {
            if( c == '.' ) {
                r.push_back(stoi(s));
                s = "";
                continue;
            }
            s += c;
        }
        r.push_back(stoi(s));

        // fill up to size with 0's
        size_t rs = r.size();
        if( rs < l )
            r.insert(r.end(),l - rs, 0);

        return r;
    }
};



int main() {

    Solution s;

    assert(s.compareVersion("0.1","1.1") == -1);
    assert(s.compareVersion("1.0.1","1") == 1);
    assert(s.compareVersion("7.5.2.4","7.5.3") == -1);
    assert(s.compareVersion("1.01","1.001") == 0);
    assert(s.compareVersion("1.0","1.0.0") == 0);

    return 0;
}
