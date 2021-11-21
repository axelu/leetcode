#include <iostream>
#include <cassert>

#include <string>
#include <cmath>

using namespace std;

// 171. Excel Sheet Column Number
// https://leetcode.com/problems/excel-sheet-column-number
// day 10 problem of the August 2020 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3419/

class Solution {
public:
    int titleToNumber(string s) {

        if ( s.length() > 7 ) return 2147483647;
        if ( s.length() == 7 && s > "FXSHRXW" ) return 2147483647; 

        int i = 0;

        for (auto it = s.rbegin(); it != s.rend(); ++it) {

            /*if ( it - s.rbegin() == 0 ) {
                i += *it - 'A' + 1;
            } else {
                i += ( *it - 'A' + 1 ) * ( (it - s.rbegin()) * 26 );
            }*/
            // cout << it - s.rbegin() << endl;
            // if ( it - s.rbegin < 6 ) {
                i += ( *it - 'A' + 1 ) * ( pow(26, it - s.rbegin()) );
            // } else if ( it -s.rbegin() == 6 ) {
                // danger zone
            // } else {
            //    i = 2147483647;
            //    break;
            // }
        }


        return i;
    }
};

int main() {

    Solution s;

    // unclear what to return if
    //     input is empty string
    //     input string is longer than 7
    //     input string contains anything other than A-Z
    //  it appears leetcode expects a Runtime Error to be raised
    //     input string 'greater than' FXSHRXW
    //  it appears leetcode return 2147483647
    
    // assert(s.titleToNumber("") == NNN);
    // assert(s.titleToNumber("AFXSHRXW") == NNN);
    // assert(s.titleToNumber("a") == NNN);
    // assert(s.titleToNumber("FXSHRXX") == 2147483647);

    assert(s.titleToNumber("A") == 1);
    cout << s.titleToNumber("Z") << endl;
    assert(s.titleToNumber("Z") == 26);
    assert(s.titleToNumber("AA") == 27);
    assert(s.titleToNumber("AB") == 28);
    assert(s.titleToNumber("AZ") == 52);
    assert(s.titleToNumber("BA") == 53);
    assert(s.titleToNumber("ZY") == 701);
    assert(s.titleToNumber("ZZ") == 702);
    assert(s.titleToNumber("AAA") == 703);
    assert(s.titleToNumber("FXSHRXW") == 2147483647); // max positive int
    cout << s.titleToNumber("AAAAAA") << endl; // 12356631 
    cout << s.titleToNumber("ZZZZZZ") << endl; // 321272406
    cout << s.titleToNumber("FXSHRXX") << endl;
    assert(s.titleToNumber("FXSHRXX") == 2147483647);


    return 0;
}
