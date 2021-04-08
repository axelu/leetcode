#include <iostream>
#include <cassert>

#include <string>

using namespace std;

// https://leetcode.com/problems/integer-to-roman/

class Solution {
public:
    string intToRoman(int num) {

        if ( num == 0 ) return "";

        // I             1
        // IV            4
        // V             5
        // IX            9
        // X             10
        // XL            40
        // L             50
        // XC            90
        // C             100
        // CD            400
        // D             500
        // CM            900
        // M             1000

        string r;
        int d = 1000;
        while ( d >= 1 ) {
            int f = num / d;

            switch(d) {
                case 1000: if ( 3 >= f && f >= 1 ) {
                               r.append(f, 'M');
                               num = num % d;
                           }
                           if ( num / 900 == 1 ) {
                               r.append("CM");
                               num = num % 900;
                           }
                           d = 500;
                           break;
                case 500:  if ( f == 1 ) {
                               r.append("D");
                               num = num % d;
                           } else if ( num / 400 == 1 ) {
                               r.append("CD");
                               num = num % 400;
                           }
                           d = 100;
                           break;
                case 100:  if ( 3 >= f && f >= 1 ) {
                               r.append(f, 'C');
                               num = num % d;
                           }
                           if ( num / 90 == 1 ) {
                               r.append("XC");
                               num = num % 90;
                           }
                           d = 50;
                           break;
                case 50:   if ( f == 1 ) {
                               r.append("L");
                               num = num % d;
                           } else if ( num / 40 == 1 ) {
                               r.append("XL");
                               num = num % 40;
                           }
                           d = 10;
                           break;
                case 10:   if ( 3 >= f && f >= 1 ) {
                               r.append(f, 'X');
                               num = num % d;
                           }
                           if ( num / 9 == 1 ) {
                               r.append("IX");
                               num = num % 9;
                           }
                           d = 5;
                           break;
                case 5:    if ( f == 1 ) {
                               r.append("V");
                               num = num % d;
                           } else if ( num / 4 == 1 ) {
                               r.append("IV");
                               num = num % 4;
                           }
                           d = 1;
                           break;
                default:   r.append(f, 'I'); // case 1
                           d = 0; // ends the loop
                           break;
            }
        };
        
        return r;
    }
};

int main() {

    Solution s;

    assert(s.intToRoman(3) == "III");
    assert(s.intToRoman(4) == "IV");
    assert(s.intToRoman(9) == "IX");
    assert(s.intToRoman(58) == "LVIII");
    assert(s.intToRoman(1994) == "MCMXCIV");

    for (int i = 0; i <= 3999; i++) {
        cout << s.intToRoman(i) << endl;
    }


    return 0;
}
