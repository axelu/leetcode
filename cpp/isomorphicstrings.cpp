#include <iostream>
#include <cassert>

#include <unordered_map>
#include <vector>
#include <string>

// Isomorphic Strings
// https://leetcode.com/problems/isomorphic-strings/

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        // assuming both strings are the same length
        if( s.empty() || s.size() == 1 ) return true;
        
        unordered_map<char,char> m1; // key'd by char from s
        unordered_map<char,char> m2; // key'd by char from t
        auto itt = t.begin();
        for(char c : s) {
            
            auto p = m1.insert({c,*itt});
            if( !p.second ) if( p.first->second != *itt ) return false;

            p = m2.insert({*itt,c});
            if( !p.second ) if( p.first->second != c ) return false;

            ++itt;
        }

        return true;
    }
};

int main() {
    Solution s;
    string a;
    string b;

    a = "add";
    b = "egg";
    cout << s.isIsomorphic(a,b) << endl; // expect true 1

    a = "ab";
    b = "aa";
    cout << s.isIsomorphic(a,b) << endl; // expect false 0

    a = "title";
    b = "paper";
    cout << s.isIsomorphic(a,b) << endl; // expect true 1

    a = "foo";
    b = "bar";
    cout << s.isIsomorphic(a,b) << endl; // expect false 0


   

    return 0;
}
