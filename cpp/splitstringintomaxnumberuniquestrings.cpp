
// Split a String Into the Max Number of Unique Substrings
// https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/submissions/

#include <iostream>
#include <cassert>

#include <string>
#include <vector>
#include <algorithm>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int maxUniqueSplit(string s) {

        vector<string> r;
        _nbrUnique = 1;
        _split(s, 0, r);

        return _nbrUnique;
    }
private:
    int _nbrUnique;

    void _split(string& s, int pos, vector<string>& r) {
        // max possible is if each letter is unique, if reached that we are good
        if( _nbrUnique == s.size() ) return;

        if( pos == s.size() ) return;

        for(int l = 1; l <= s.size() - pos; ++l) {
            string u = s.substr(pos, l);
            auto f = find(r.begin(), r.end(), u);
            if( f == r.end() ) {
                // not found
                r.push_back(u);
                _nbrUnique = max(_nbrUnique, (int) r.size());
                _split(s, pos + l, r);
                r.pop_back();
            }
        }
    }
};


int main() {

    Solution s;
    string sin;

    sin  = "ababccc"; // 5
    cout << "sin " << sin << endl;
    assert(s.maxUniqueSplit(sin) == 5);

    sin  = "aba";
    cout << "sin " << sin << endl;
    assert(s.maxUniqueSplit(sin) == 2);

    sin  = "aa";
    cout << "sin " << sin << endl;
    assert(s.maxUniqueSplit(sin) == 1);

    sin  = "ababb";
    cout << "sin " << sin << endl;
    assert(s.maxUniqueSplit(sin) == 3);

    // case 59 / 95 initially wrong answer
    sin  = "gahbag";
    cout << "sin " << sin << endl;
    assert(s.maxUniqueSplit(sin) == 5);

    sin  = "addbsd";
    cout << "sin " << sin << endl;
    assert(s.maxUniqueSplit(sin) == 5);

    // case 75 / 95 initially wrong answer
    sin  = "wwwzfvedwfvhsww"; // 11
    cout << "sin " << sin << endl;
    assert(s.maxUniqueSplit(sin) == 11);


    return 0;
}

