
// Rearrange Spaces Between Words
// https://leetcode.com/contest/weekly-contest-207/problems/rearrange-spaces-between-words/

#include <iostream>
#include <cassert>

#include <string>
#include <algorithm>
#include <vector>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    string reorderSpaces(string text) {
        // count spaces
        auto nbrSpaces = count(text.begin(), text.end(), ' ');

        if( nbrSpaces == 0 ) return text;

        string word = "";
        vector<string> words;
        for(char c : text) {

            if( c != ' ' ) {
                word += c;
            } else {
                if ( word != "" ) {
                    words.push_back(word);
                    word = "";
                }
            }
        }
        if ( word != "" )
            words.push_back(word);

        int nbrSpacesBetween = 0;
        int nbrSpacesAfter = nbrSpaces;
        if( words.size() > 1 ) {
            nbrSpacesBetween = nbrSpaces / ( words.size() - 1 );
            nbrSpacesAfter = nbrSpaces % ( words.size() - 1 );
        }

        string r = words[0];
        for(auto it = words.begin() + 1; it != words.end(); ++it) {
            for(int i = 0; i < nbrSpacesBetween; ++i)
                r += ' ';
            r += *it;
        }
        if ( nbrSpacesAfter > 0 ) {
            for(int i = 0; i < nbrSpacesAfter; ++i)
                r += ' ';
        }

        return r;
    }
};

int main() {

    Solution s;
    string sin;
    string sout;

    sin  = "  this   is  a sentence ";
    sout = "this   is   a   sentence";
    assert(s.reorderSpaces(sin) == sout);

    sin  = " practice   makes   perfect";
    sout = "practice   makes   perfect ";
    assert(s.reorderSpaces(sin) == sout);

    sin  = "hello   world";
    sout = "hello   world";
    assert(s.reorderSpaces(sin) == sout);

    sin  = "  walks  udp package   into  bar a";
    sout = "walks  udp  package  into  bar  a ";
    assert(s.reorderSpaces(sin) == sout);

    sin  = "a";
    sout = "a";
    assert(s.reorderSpaces(sin) == sout);

    sin  = "hello   world  ";
    sout = "hello     world";
    assert(s.reorderSpaces(sin) == sout);

    sin  = "  hello";
    sout = "hello  ";
    assert(s.reorderSpaces(sin) == sout);



    return 0;
}
