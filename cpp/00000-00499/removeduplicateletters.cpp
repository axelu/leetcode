
// day 11 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/560/week-2-october-8th-october-14th/3491/
// 316. Remove Duplicate Letters
// https://leetcode.com/problems/remove-duplicate-letters/
// https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/

#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>
#include <cmath>
#include <climits>
#include <bitset>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    string removeDuplicateLetters(string s) {
        auto n = s.size();

        int hidx[26]; // highest idx of char a-z in string s; a = 0, ..., z = 25
        for(int i = 0; i < n; ++i)
              hidx[s[i]-'a'] = i;
        
        int added = 0; // bitmask to track which char is already in our return;
        string r = s.substr(0,1);   // add 1st char from s to return
        added ^= 1 << (s[0]-'a');   // mark char as added to our return
        for(int i = 1; i < n; ++i) {
            char ch = s[i]-'a'; 

            // skip if we already added this char to our return
            if( (added >> ch) & 1 ) continue;

            // last char in our return currently
            char l = r.back() - 'a';

            // if the last char in our return is greater AND 
            // that last char will come up later in s again, we remove it before
            // before adding our current char
            while( l > ch && i < hidx[l] ) {
                r.pop_back();
                added &= ~(1 << l); // mark last char as not yet added to return
                if( r.empty() ) break;
                l = r.back() - 'a';
            }

            r.push_back(s[i]);      
            added ^= 1 << ch; // mark char as added
        }

        return r;
    }
};


int main() {

    Solution s;
    string input;
    string r;

    // int added = 3;
    // cout << bitset<26>(added).to_string() << endl;
    // int i = 2; 
    // if( (added >> i) & 1 ) {
    //     cout << i << "th bit is set" << endl;
    // }
    // set the ith bit
    // i = 25;
    // added ^= 1 << i;
    // cout << bitset<26>(added).to_string() << endl;
    // unsetting the ith bit
    // added &= ~(1 << i);
    // cout << bitset<26>(added).to_string() << endl;

    input = "bcabc";
    cout << input << endl;
    r = s.removeDuplicateLetters(input);
    cout << "result " << r << endl;
    assert(r == "abc");

    input = "cbacdcbc";
    cout << input << endl;
    r = s.removeDuplicateLetters(input);
    cout << "result " << r << endl;
    assert(r == "acdb");

    input = "bcabccffeeg";
    cout << input << endl;
    r = s.removeDuplicateLetters(input);
    cout << "result " << r << endl;
    assert(r == "abcfeg");

    input = "bcabccfeefg";
    cout << input << endl;
    r = s.removeDuplicateLetters(input);
    cout << "result " << r << endl;
    assert(r == "abcefg");

    cout << "random" << endl;
    srand(time(nullptr)); // use current time as seed for random generator
    int rdm;
    input = "";
    int n = 10000;
    for(int i = 0; i < n; ++i) {
        int rdm = rand() % 26; // random in the range 0 to 25
        input += rdm + 'a';
    }
    cout << input << endl;
    r = s.removeDuplicateLetters(input);
    cout << "result " << r << endl;

    return 0;
}
