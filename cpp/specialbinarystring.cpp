
// Special Binary String
// https://leetcode.com/problems/special-binary-string/





#include <iostream>
#include <cassert>

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    string makeLargestSpecial(string S) {
        auto Ss = S.size();
        if( Ss == 2 ) return S;

        // check if all 1s are already in the front
        auto it  = S.begin();
        auto ith = it + Ss / 2;
        auto f = find(it, ith, '0');
        if( f == ith ) return S;

        return _makeLargestSpecial(S);
    }
private:
    string _makeLargestSpecial(string S) {

        // cout << "sub " << S << endl;

        vector<string> v;

        int c0 = 0; // count 0s
        int c1 = 0; // count 1s
        auto its = S.begin();
        auto idx = its;
        for(; its != S.end(); ++its) {
            if( *its == '0' ) {
                ++c0;
            } else {
                ++c1;
            }
            if( c0 == c1 ) {
                string s(idx, its + 1);
                // cout << "pushing " << s << endl;
                v.push_back(s);
                idx = its + 1;
            }
        }

        for(auto itv = v.begin(); itv != v.end(); ++itv) {
            // cout << *itv << endl;
            string inner = itv->substr(1, itv->size() - 2);
            *itv = '1' + _makeLargestSpecial(inner) + '0';
        }

        sort(v.begin(), v.end(),[](string str1, string str2){
            return str2 < str1;
        });

        string r;
        for(string s : v)
            r.append(s);

        return r;
    }
};

int main() {

    Solution s;
    string S;
    string r;

    S = "10";
    cout << "S " << S << endl;
    assert(s.makeLargestSpecial(S) == "10");

    /*
    S = "01"; // not a valid test case as a special string starts with 1
    assert(s.makeLargestSpecial(S) == "10"); */

    S = "1100";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "1100");

    S = "11011000";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "11100100");

    S = "11100010";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "11100010");

    S = "10110100";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "11010010");

    S = "11101000";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "11101000");

    S = "1110010100";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "1110010100");

    // case 35 / 86
    S = "101101011000";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "111001010010");

    // case 21 / 86
    S = "1011100100101100";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "1110010011001010");

    // case 54 / 86
    S = "11101001111001010000110010";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "11111001010001101000110010");

    // case 56 / 86
    S = "1101010011111011010000010010";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "1111110100100001001101010010");

    // case 62 / 86
    S = "1101001110001101010110010010";
    cout << "S " << S << endl;
    // s.makeLargestSpecial(S);
    assert(s.makeLargestSpecial(S) == "1110010101010011100011010010");

    return 0;
}
