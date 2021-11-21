#include <iostream>
#include <cassert>

#include <string>
// #include <unordered_set>

// 3. Longest Substring Without Repeating Characters
// https://leetcode.com/problems/longest-substring-without-repeating-characters/

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        if ( s.empty() ) return 0;
        if ( s.size() == 1 ) return 1;

        // debug
        // cout << "input: " << s << endl;
        // cout << "input size: " << s.size() << endl;
        // cout << "end - begin: " << s.end() - s.begin() << endl; // = s.size()

        int r = 0;
        int i = 0;
        int b = 0;

        for (auto it = s.begin(); it != s.end(); ++it) {
     
            // debug
            // cout << "pos = " << it - s.begin() << endl;
            // cout << "i = " << i << endl;
            // cout << "b = " << b << endl;
            // cout << s.substr(b,i) << endl;

            auto n = s.substr(b,i).find(*it);
            if ( n != string::npos ) {
                // debug
                // cout << "found " << *it << " at pos " << n << endl;
                // cout << "number of chars left = " << s.end() - it << endl;

                if ( i >= (s.size() - b + 1) ) break;

                if ( i > r ) r = i;

                i -= n + 1;
                b += n + 1;

            }

            i++;
            
        }

        // debug
        // int tmp = ( i > r ) ? i : r;
        // cout << "result = " << tmp << endl;
        // cout << endl;

        return ( i > r ) ? i : r;
    }
};

int main() {

    Solution s;

    //string str = "davdf";
    //auto n = str.find("a",0);
    //if (n == string::npos) {
    //    cout << "not found\n";
    //} else {
    //    cout << "found: " << str.substr(n) << '\n';
    //}
    //cout << str.substr(0,3) << endl;
    //n = str.substr(0,3).find("d");


    assert(s.lengthOfLongestSubstring("") == 0);
    assert(s.lengthOfLongestSubstring("a") == 1);
    assert(s.lengthOfLongestSubstring("abcabcbb") == 3);
    assert(s.lengthOfLongestSubstring("bbbbb") == 1);
    assert(s.lengthOfLongestSubstring("pwwkew") == 3);
    assert(s.lengthOfLongestSubstring(" ab") == 3);
    assert(s.lengthOfLongestSubstring("abcabcabcd") == 4);
    assert(s.lengthOfLongestSubstring("abcabcdab") == 4);
    assert(s.lengthOfLongestSubstring("abcabcdabcd") == 4);
    assert(s.lengthOfLongestSubstring("abcabcdabcde") == 5);
    assert(s.lengthOfLongestSubstring("davdf") == 4);
    assert(s.lengthOfLongestSubstring("dvdf") == 3);

    return 0;
}
