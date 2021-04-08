#include <iostream>
#include <cassert>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>

using namespace std;

// day 14 of the August 2020 challenge
// Longest Palindrome
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3423/

class Solution {
public:
    int longestPalindrome(string s) {

        if ( s.empty() ) return 0;
        if ( s.size() == 1 ) return 1;
      
        // int sum = 0;
        int count_uneven = -1;
        unordered_set<char> us;
        for(char c : s) {
            // sum += c;
            auto r = us.insert(c);
            if ( !r.second ) {
                us.erase(r.first);
                count_uneven--;
            } else {
                count_uneven++;
            }
        }

        // return ( sum / s.size() == s[0] && count_uneven <= 0 ) ? s.size() : s.size() - abs(count_uneven);
        return ( count_uneven <= 0 ) ? s.size() : s.size() - count_uneven;

        /*
        unordered_map<char,int> m;
        for(char c : s) {
            auto r = m.insert({c, 1});
            if ( !r.second ) r.first->second++;
        }

        // sum all even numbers + largest uneven number + all other (uneven numbers - 1)
        int l = 0;
        bool hasUneven = false;
        for(auto p : m) {
            if ( p.second % 2 == 0 ) {
                l += p.second;
            } else {
                l += p.second - 1;
                hasUneven = true;
            }
        }

        return ( hasUneven ) ? l + 1 : l;
        */
    }
};

int main() {

    Solution s;
    
    assert(s.longestPalindrome("abccccdd") == 7);
    assert(s.longestPalindrome("ababab") == 5);
    assert(s.longestPalindrome("aaabbb") == 5);
    assert(s.longestPalindrome("bb") == 2);
    assert(s.longestPalindrome("bbb") == 3);
    assert(s.longestPalindrome("tattarrattat") == 12);


    return 0;
}
