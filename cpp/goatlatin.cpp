#include <iostream>
#include <cassert>

#include <string>
#include <unordered_set>

using namespace std;

// day 19 August 2020 challenge
// Goat Latin

class Solution {
public:
    string toGoatLatin(string S) {
        if ( S.empty() ) return S;

        auto it = find_if_not(S.begin(), S.end(), [](char c){return c == ' ';});
        S.erase(S.begin(), it);
        auto rt = find_if_not(S.rbegin(), S.rend(), [](char c){return c == ' ';});
        S.erase(rt.base(),S.end());

        unordered_set<char> vowels = {'a','A','e','E','i','I','o','O','u','U'};
        string R;
        int i = 1;
        string a;
        int mode = 0; // 0 look for non space, 1 look for space
        for(auto it = S.begin(); it != S.end(); ++it) {
            if ( mode == 0 ) {
                // looking for non space
                auto search = vowels.find(*it);
                if (search != vowels.end()) {
                    // found a vowel
                    a = "ma";
                    mode = 1;
                    R.push_back(*it);
                    continue;
                } else if ( *it != ' ' ) {
                    // found a consonant
                    a = *it; a.append("ma");
                    mode = 1;
                    continue;
                }
            } else {
                // looking for space (mode 1)
                if ( *it == ' ' ) {
                    R.append(a);
                    for (int n = 1; n <= i; ++n) R.push_back('a');
                    ++i;
                    if ( it + 1 != S.end() ) R.push_back(' '); // not if at end
                    mode = 0;
                } else {
                    R.push_back(*it);
                }
            }
        }
        // closing out meaning last char was not a space
        if ( mode == 1 ) {
            R.append(a);
            for (int n = 1; n <= i; ++n) R.push_back('a');
        }


        return R;
    }
};
