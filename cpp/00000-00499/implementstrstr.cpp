#include <iostream>
#include <cassert>

#include <string>

using namespace std;

// 28. Implement strStr()
// https://leetcode.com/problems/implement-strstr/

class Solution {
public:
    int strStr(string haystack, string needle) {

        // eliminating the obvious
        if ( needle.empty() ) return 0;
        if ( haystack.empty() ) return -1;
        if ( needle.size() > haystack.size() ) return -1;
        if ( needle.size() == haystack.size() ) {
            if ( needle == haystack ) {
                return 0;
            } else {
                return -1;
            }
        }

        auto ith = haystack.begin();
        for(; ith != haystack.begin() + (haystack.size() - needle.size()); ++ith) {

            if ( *ith == needle[0] ) {
                if ( needle.size() == 1 ) return ith - haystack.begin();
                int i = 1;
                for (auto itn = needle.begin() + 1; itn != needle.end(); ++itn) {
                    if ( *itn != *(ith + i) ) {
                        break;
                    }
                    i++;
                }
                if ( i == needle.size() ) return ith - haystack.begin();
            }
        }

        // if still here, then compare last possible part
        if ( *ith != needle[0] ) {
            return -1;
        } else {
            if ( haystack.substr(haystack.size() - needle.size()) != needle ) {
                return -1;
            } else {
                return haystack.size() - needle.size();
            }
        }

    }
};

int main() {

    Solution s;

    assert(s.strStr("","") == 0);
    assert(s.strStr("a","") == 0);
    assert(s.strStr("","a") == -1);

    assert(s.strStr("hello", "helloo") == -1);
    assert(s.strStr("hello", "hello") == 0);

    assert(s.strStr("hello", "l") ==2);
    assert(s.strStr("hello", "ll") == 2);
    assert(s.strStr("aaaaa", "bba") == -1);

    assert(s.strStr("hello", "hell") == 0);
    assert(s.strStr("abchello", "hello") == 3);
    assert(s.strStr("abchello", "elloo") == -1);


    return 0;
}
