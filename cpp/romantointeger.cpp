#include <iostream>
#include <cassert>

#include <string>

using namespace std;

// https://leetcode.com/problems/roman-to-integer/

class Solution {
public:
    int romanToInt(string s) {

        int i = 0;

        for (auto it = s.begin(); it != s.end(); ++it) {

            // I             1
            // V             5
            // X             10
            // L             50
            // C             100
            // D             500
            // M             1000
            
            switch(*it) {
                case 'I': if ( it + 1 != s.end() ) {
                            if ( *(it + 1) == 'V' ) {
                                i += 4;
                                ++it;
                            } else if ( *(it + 1) == 'X' ) {
                                i += 9;
                                ++it;
                            } else {
                              i += 1;
                            }
                          } else {
                              i += 1;
                          }
                          break;
                case 'V': i += 5;
                          break;
                case 'X': if ( it + 1 != s.end() ) {
                            if ( *(it + 1) == 'L' ) {
                                i += 40;
                                ++it;
                            } else if ( *(it + 1) == 'C' ) {
                                i += 90;
                                ++it;
                            } else {
                              i += 10;
                            }
                          } else {
                              i += 10;
                          }
                          break;
                case 'L': i += 50;
                          break;
                case 'C': if ( it + 1 != s.end() ) {
                            if ( *(it + 1) == 'D' ) {
                                i += 400;
                                ++it;
                            } else if ( *(it + 1) == 'M' ) {
                                i += 900;
                                ++it;
                            } else {
                              i += 100;
                            }
                          } else {
                              i += 100;
                          }
                          break;
                case 'D': i += 500;
                          break;
                case 'M': i += 1000;
                          break;
                default:  break;
            }




        }

        return i;
    }
};

int main() {

    Solution s;

    assert(s.romanToInt("III") == 3);
    assert(s.romanToInt("IV") == 4);
    assert(s.romanToInt("IX") == 9);
    assert(s.romanToInt("LVIII") == 58);
    assert(s.romanToInt("MCMXCIV") == 1994);


    return 0;
}
